#include "yolov5.h"
#include <stdc++.h>
#include <Bits.h>
#include <chrono>

#define NOMINMAX
const int INPUT_WIDTH = 640;
const int INPUT_HEIGHT = 640;
const float SCORE_THRESHOLD = 0.5;
const float NMS_THRESHOLD = 0.45;
const float CONFIDENCE_THRESHOLD = 0.45;
cv::Mat blackImgPCA;
cv::Mat blob;

bool isProcessing = false;
int sendPCAflag = 0;
float max =0;
int index =0;
int classID = 0;
int boxID = 0;
struct OutputSeg
{
    int id;
    float confidence;
    cv::Rect box;
    cv::Mat boxMask;
};

// Text parameters.
const float FONT_SCALE = 0.3;
const int FONT_FACE = cv::FONT_HERSHEY_SIMPLEX;
const int THICKNESS = 1;
cv::Scalar RED = cv::Scalar(0,0,255);
cv::Scalar BLUE = cv::Scalar(255, 178, 50);
cv::Scalar WHITE = cv::Scalar(255, 255, 255);
cv::Scalar BLACK = cv::Scalar(0, 0, 0);
cv::Scalar YELLOW = cv::Scalar(0, 255, 255);
struct MaskParams
{
    int segChannels = 32;
    int segWidth = 160;
    int segHeight = 160;
    int netWidth = 640;
    int netHeight = 640;
    float maskThreshold = 0.5;
    cv::Size srcImgShape;
    cv::Vec4d params;
};


void Yolov5::delay(int milliseconds) {
    auto start = std::chrono::high_resolution_clock::now();
    while (true) {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
        if (elapsed.count() >= milliseconds) {
            break;
        }
    }
}


Yolov5::Yolov5(QObject *parent)
    : QThread{parent}
{
    // Load class list.
    std::ifstream ifs("config/class_seg.txt");
    std::string line;
    while (getline(ifs, line))
    {
        class_name.push_back(line);
    }
    net = cv::dnn::readNet("config/best2.onnx"); //best2
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
//        net = readNet("config/final.onnx");
//    //    net.setPreferableBackend(DNN_BACKEND_OPENCV);// DNN_BACKEND_INFERENCE_ENGINE DNN_BACKEND_CUDA
//    //    net.setPreferableTarget(DNN_TARGET_CPU);//DNN_TARGET_CUDA
//        net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
//        net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA_FP16);
}

//**********************************************************
//Function for Yolov5 Segmentation
void LetterBox(const cv::Mat& image, cv::Mat& outImage,
               cv::Vec4d& params, //[ratio_x,ratio_y,dw,dh]
               const cv::Size& newShape = cv::Size(640, 640),
               bool autoShape = false,
               bool scaleFill = false,
               bool scaleUp = true,
               int stride = 32,
               const cv::Scalar& color = cv::Scalar(114, 114, 114))
{
    cv::Size shape = image.size();
    float r = min((float)newShape.height / (float)shape.height, (float)newShape.width / (float)shape.width);
    if (!scaleUp)
    {
        r = min(r, 1.0f);
    }

    float ratio[2]{ r, r };
    int new_un_pad[2] = { (int)std::round((float)shape.width * r),(int)std::round((float)shape.height * r) };

    auto dw = (float)(newShape.width - new_un_pad[0]);
    auto dh = (float)(newShape.height - new_un_pad[1]);

    if (autoShape)
    {
        dw = (float)((int)dw % stride);
        dh = (float)((int)dh % stride);
    }
    else if (scaleFill)
    {
        dw = 0.0f;
        dh = 0.0f;
        new_un_pad[0] = newShape.width;
        new_un_pad[1] = newShape.height;
        ratio[0] = (float)newShape.width / (float)shape.width;
        ratio[1] = (float)newShape.height / (float)shape.height;
    }

    dw /= 2.0f;
    dh /= 2.0f;

    if (shape.width != new_un_pad[0] && shape.height != new_un_pad[1])
        cv::resize(image, outImage, cv::Size(new_un_pad[0], new_un_pad[1]));
    else
        outImage = image.clone();

    int top = int(std::round(dh - 0.1f));
    int bottom = int(std::round(dh + 0.1f));
    int left = int(std::round(dw - 0.1f));
    int right = int(std::round(dw + 0.1f));
    params[0] = ratio[0];
    params[1] = ratio[1];
    params[2] = left;
    params[3] = top;
    cv::copyMakeBorder(outImage, outImage, top, bottom, left, right, cv::BORDER_CONSTANT, color);
}


void pre_process(cv::Mat& image, cv::Vec4d& params)
{
    cv::Mat input_image;
    LetterBox(image, input_image, params, cv::Size(INPUT_WIDTH, INPUT_HEIGHT));
    cv::dnn::blobFromImage(input_image, blob, 1. / 255., cv::Size(INPUT_WIDTH, INPUT_HEIGHT), cv::Scalar(0, 0, 0), true, false);
}


void process(cv::dnn::Net& net, std::vector<cv::Mat>& outputs)
{
    net.setInput(blob);
    std::vector<std::string> output_layer_names{ "output0","output1" };
    net.forward(outputs, output_layer_names);
}


void GetMask(const cv::Mat& maskProposals, const cv::Mat& mask_protos, OutputSeg& output, const MaskParams& maskParams)
{
    int seg_channels = maskParams.segChannels;
    int net_width = maskParams.netWidth;
    int seg_width = maskParams.segWidth;
    int net_height = maskParams.netHeight;
    int seg_height = maskParams.segHeight;
    float mask_threshold = maskParams.maskThreshold;
    cv::Vec4f params = maskParams.params;
    cv::Size src_img_shape = maskParams.srcImgShape;
    cv::Rect temp_rect = output.box;

    //crop from mask_protos
    int rang_x = floor((temp_rect.x * params[0] + params[2]) / net_width * seg_width);
    int rang_y = floor((temp_rect.y * params[1] + params[3]) / net_height * seg_height);
    int rang_w = ceil(((temp_rect.x + temp_rect.width) * params[0] + params[2]) / net_width * seg_width) - rang_x;
    int rang_h = ceil(((temp_rect.y + temp_rect.height) * params[1] + params[3]) / net_height * seg_height) - rang_y;

    rang_w = MAX(rang_w, 1);
    rang_h = MAX(rang_h, 1);
    if (rang_x + rang_w > seg_width)
    {
        if (seg_width - rang_x > 0)
            rang_w = seg_width - rang_x;
        else
            rang_x -= 1;
    }
    if (rang_y + rang_h > seg_height)
    {
        if (seg_height - rang_y > 0)
            rang_h = seg_height - rang_y;
        else
            rang_y -= 1;
    }

    std::vector<cv::Range> roi_rangs;
    roi_rangs.push_back(cv::Range(0, 1));
    roi_rangs.push_back(cv::Range::all());
    roi_rangs.push_back(cv::Range(rang_y, rang_h + rang_y));
    roi_rangs.push_back(cv::Range(rang_x, rang_w + rang_x));

    //crop
    cv::Mat temp_mask_protos = mask_protos(roi_rangs).clone();
    cv::Mat protos = temp_mask_protos.reshape(0, { seg_channels,rang_w * rang_h });
    cv::Mat matmul_res = (maskProposals * protos).t();
    cv::Mat masks_feature = matmul_res.reshape(1, { rang_h,rang_w });
    cv::Mat dest, mask;

    //sigmoid
    cv::exp(-masks_feature, dest);
    dest = 1.0 / (1.0 + dest);

    int left = floor((net_width / seg_width * rang_x - params[2]) / params[0]);
    int top = floor((net_height / seg_height * rang_y - params[3]) / params[1]);
    int width = ceil(net_width / seg_width * rang_w / params[0]);
    int height = ceil(net_height / seg_height * rang_h / params[1]);

    cv::resize(dest, mask, cv::Size(width, height), cv::INTER_NEAREST);
    mask = mask(temp_rect - cv::Point(left, top)) > mask_threshold;
    output.boxMask = mask;
}


void draw_result(cv::Mat & image, std::vector<OutputSeg> result, std::vector<std::string> class_name)
{
    cv::Mat mask = image.clone();
    for (int i = 0; i < result.size(); i++)
    {
        std::string label = class_name[result[i].id] + ":" + cv::format("%.2f", result[i].confidence);
        if(result[i].id==0){
            cv::rectangle(image, result[i].box, RED, THICKNESS);
            mask(result[i].box).setTo(RED, result[i].boxMask);
            cv::putText(image, label, cv::Point(result[i].box.x, result[i].box.y), FONT_FACE, FONT_SCALE, RED);
        }
        if(result[i].id==1){
            cv::rectangle(image, result[i].box, BLUE, 1);
            mask(result[i].box).setTo(BLUE, result[i].boxMask);
            cv::putText(image, label, cv::Point(result[i].box.x, result[i].box.y), FONT_FACE, FONT_SCALE, BLUE);
        }
    }
    addWeighted(image, 0.6, mask, 0.5, 0, image);
}

void draw_result_black(cv::Mat & image, std::vector<OutputSeg> result, std::vector<std::string> class_name)
{
    if (result.size() > 0)
    {
        float max = result[0].confidence;
        index = 0;
        for (int i = 0; i < result.size(); i++)
        {
            if(max < result[i].confidence){
                max = result[i].confidence;
                index = i;
            }
        }
        cv::Mat blackImg(480, 640, CV_8UC3, BLACK);
        image = blackImg.clone();
        cv::Mat mask = image.clone();
        mask(result[index].box).setTo(YELLOW, result[index].boxMask);
        addWeighted(image, 0.6, mask, 1, 0, image);
        classID = result[index].id;
    }
}


cv::Mat Yolov5::post_process(cv::Mat& image, std::vector<cv::Mat>& outputs, const std::vector<std::string>& class_name, cv::Vec4d& params)
{
    std::vector<int> class_ids;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;
    std::vector<std::vector<float>> picked_proposals;

    float* data = (float*)outputs[0].data;

    const int dimensions = 39;	//5+class+32
    const int rows = 25200; 	//(640/8)*(640/8)*3+(640/16)*(640/16)*3+(640/32)*(640/32)*3
    for (int i = 0; i < rows; ++i)
    {
        float confidence = data[4];
        if (confidence >= CONFIDENCE_THRESHOLD)
        {
            float* classes_scores = data + 5;
            cv::Mat scores(1, class_name.size(), CV_32FC1, classes_scores);
            cv::Point class_id;
            double max_class_score;
            cv::minMaxLoc(scores, 0, &max_class_score, 0, &class_id);
            if (max_class_score > SCORE_THRESHOLD)
            {
                float x = (data[0] - params[2]) / params[0];
                float y = (data[1] - params[3]) / params[1];
                float w = data[2] / params[0];
                float h = data[3] / params[1];
                int left = max(int(x - 0.5 * w), 0);
                int top = max(int(y - 0.5 * h), 0);
                int width = int(w);
                int height = int(h);
                boxes.push_back(cv::Rect(left, top, width, height));
                confidences.push_back(confidence);
                class_ids.push_back(class_id.x);
                std::vector<float> temp_proto(data + class_name.size() + 5, data + dimensions);
                picked_proposals.push_back(temp_proto);
            }
        }
        data += dimensions;
    }

    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, SCORE_THRESHOLD, NMS_THRESHOLD, indices);

    std::vector<OutputSeg> output;
    std::vector<std::vector<float>> temp_mask_proposals;
    cv::Rect holeImgRect(0, 0, image.cols, image.rows);
    for (int i = 0; i < indices.size(); ++i)
    {
        int idx = indices[i];
        OutputSeg result;
        result.id = class_ids[idx];
        result.confidence = confidences[idx];
        result.box = boxes[idx] & holeImgRect;
        temp_mask_proposals.push_back(picked_proposals[idx]);

            output.push_back(result);
    }

    MaskParams mask_params;
    mask_params.params = params;
    mask_params.srcImgShape = image.size();
    for (int i = 0; i < temp_mask_proposals.size(); ++i)
    {
        GetMask(cv::Mat(temp_mask_proposals[i]).t(), outputs[1], output[i], mask_params);
    }


    std::vector<OutputSeg> output_main;
    for(int i=0; i<output.size();i++){
        if(output[i].box.x>=332 && (output[i].box.x+output[i].box.width)<=532 && output[i].box.y>=170 && (output[i].box.y+output[i].box.height)<=350){
            output_main.push_back(output[i]);
        }
    }

    cv::Mat img_main;

    img_main = image.clone();


    draw_result(image, output_main, class_name);


    draw_result(img_main, output_main, class_name);



    if((output_main.size()>0)&&(sendPCAflag == 0))
    {
        blackImgPCA = img_main.clone();
        draw_result_black(blackImgPCA, output_main, class_name);
        boxID = 0;
        emit sendQImagePCA(convertMattoQImage(blackImgPCA), classID);
        sendPCAflag = 10;
    }
    numberDetect = output_main.size();

    return image;
}



void Yolov5::run()
{
    while(true)
    {
        if(isYoloruning)
        {
            std::clock_t start, end;
            start = std::clock();
            delay(100);
            pre_process(frame, params);
            process(net, detections);
            frameYolo = post_process(frame, detections, class_name, params);
            imageToMain = convertMattoQImage(frameYolo);
            emit sendFrame(imageToMain);
            end = std::clock();
            timeToMain = (double(end - start) / double(CLOCKS_PER_SEC))*1000.0;
            emit sendTimeProcess(timeToMain);
            emit sendCmd(true);
        }
    }
}

void Yolov5::stop()
{
    isYoloruning = false;
}


void Yolov5::receivedFrame(QImage img)
{
    frame = convertQImagetoMat(img);
    emit sendCmd(false);
}

void Yolov5::receivedPCArequest(int flag)
{
    sendPCAflag = flag;
    // 0 = main
    // 1 = blue
    // 2 = green
}

QImage Yolov5::convertMattoQImage(cv::Mat mat)
{
    return  QImage((const unsigned char*)(mat.data), mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888).rgbSwapped();
}

cv::Mat Yolov5::convertQImagetoMat(QImage img)
{
    img = img.convertToFormat(QImage::Format_RGB888, Qt::ColorOnly).rgbSwapped();
    return cv::Mat(img.height(), img.width(), CV_8UC3, img.bits(), img.bytesPerLine()).clone();
}
void Yolov5::cmd(){
    isYoloruning = true;
}

