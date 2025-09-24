#include <iostream>
#include <opencv2/opencv.hpp>

void applyTransformations(cv::Mat& frame) {
    // 1. Размытие по Гауссу
    cv::Mat blurred;
    cv::GaussianBlur(frame, blurred, cv::Size(15, 15), 0);
    
    // 2. Обнаружение границ Canny
    cv::Mat edges;
    cv::Canny(blurred, edges, 50, 150);
    
    // 3. Преобразование в оттенки серого и обратно в BGR для цветного эффекта
    cv::Mat gray, color_edges;
    cv::cvtColor(edges, color_edges, cv::COLOR_GRAY2BGR);
    
    // 4. Наложение эффектов (смешивание оригинального и edge-изображения)
    cv::Mat result;
    cv::addWeighted(frame, 0.7, color_edges, 0.3, 0, result);
    
    // 5. Резкость (unsharp masking)
    cv::Mat sharpened;
    cv::GaussianBlur(result, sharpened, cv::Size(0, 0), 3);
    cv::addWeighted(result, 1.5, sharpened, -0.5, 0, frame);
}

int main() {
    cv::VideoCapture capture(0);
    if (!capture.isOpened()) {
        std::cerr << "Error: Cannot open camera" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        double capture_time = (double)cv::getTickCount();
        
        capture >> frame;
        if (frame.empty()) break;
        
        double process_time = (double)cv::getTickCount();
        applyTransformations(frame);
        process_time = ((double)cv::getTickCount() - process_time) / cv::getTickFrequency();
        
        double display_time = (double)cv::getTickCount();
        cv::imshow("Transformed Image", frame);
        display_time = ((double)cv::getTickCount() - display_time) / cv::getTickFrequency();
        
        capture_time = ((double)cv::getTickCount() - capture_time) / cv::getTickFrequency();
        
        // Вывод информации о времени
        std::cout << "Total: " << capture_time*1000 << "ms | "
                  << "Process: " << process_time*1000 << "ms | "
                  << "Display: " << display_time*1000 << "ms" << std::endl;

        char c = (char)cv::waitKey(1);
        if (c == 27) break;
    }

    capture.release();
    cv::destroyAllWindows();
    return 0;
}