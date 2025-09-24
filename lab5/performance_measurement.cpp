#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

class PerformanceMonitor {
private:
    int frame_count;
    double total_time;
    double process_time;
    double capture_time;
    double display_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    
public:
    PerformanceMonitor() : frame_count(0), total_time(0), process_time(0), 
                          capture_time(0), display_time(0) {}
    
    void startFrame() {
        start_time = std::chrono::high_resolution_clock::now();
    }
    
    void addCaptureTime() {
        auto now = std::chrono::high_resolution_clock::now();
        capture_time += std::chrono::duration<double>(now - start_time).count();
        start_time = now;
    }
    
    void addProcessTime() {
        auto now = std::chrono::high_resolution_clock::now();
        process_time += std::chrono::duration<double>(now - start_time).count();
        start_time = now;
    }
    
    void addDisplayTime() {
        auto now = std::chrono::high_resolution_clock::now();
        display_time += std::chrono::duration<double>(now - start_time).count();
        total_time += capture_time + process_time + display_time;
        frame_count++;
    }
    
    void printStatistics() {
        if (frame_count > 0) {
            double avg_fps = frame_count / total_time;
            double avg_total = total_time / frame_count;
            double avg_capture = capture_time / frame_count;
            double avg_process = process_time / frame_count;
            double avg_display = display_time / frame_count;
            
            std::cout << "\n=== PERFORMANCE STATISTICS ===" << std::endl;
            std::cout << "Frames processed: " << frame_count << std::endl;
            std::cout << "Total time: " << total_time << "s" << std::endl;
            std::cout << "Average FPS: " << avg_fps << std::endl;
            std::cout << "Average frame time: " << avg_total * 1000 << "ms" << std::endl;
            std::cout << "Time distribution per frame:" << std::endl;
            std::cout << "  Capture: " << avg_capture * 1000 << "ms (" 
                      << (avg_capture/avg_total)*100 << "%)" << std::endl;
            std::cout << "  Process: " << avg_process * 1000 << "ms (" 
                      << (avg_process/avg_total)*100 << "%)" << std::endl;
            std::cout << "  Display: " << avg_display * 1000 << "ms (" 
                      << (avg_display/avg_total)*100 << "%)" << std::endl;
        }
    }
};

void processFrame(cv::Mat& frame) {
    // Произвольное преобразование для тестирования
    cv::Mat blurred, edges, result;
    
    // Размытие
    cv::GaussianBlur(frame, blurred, cv::Size(5, 5), 0);
    
    // Обнаружение границ
    cv::Canny(blurred, edges, 50, 150);
    
    // Цветное наложение
    cv::Mat color_edges;
    cv::cvtColor(edges, color_edges, cv::COLOR_GRAY2BGR);
    cv::addWeighted(frame, 0.8, color_edges, 0.2, 0, result);
    
    frame = result;
}

int main() {
    cv::VideoCapture capture(0);
    if (!capture.isOpened()) {
        std::cerr << "Error: Cannot open camera" << std::endl;
        return -1;
    }

    PerformanceMonitor monitor;
    cv::Mat frame;
    int frames_to_process = 100; // Обработать 100 кадров для статистики
    
    std::cout << "Processing " << frames_to_process << " frames for performance analysis..." << std::endl;
    
    for (int i = 0; i < frames_to_process; ++i) {
        monitor.startFrame();
        
        capture >> frame;
        if (frame.empty()) break;
        monitor.addCaptureTime();
        
        processFrame(frame);
        monitor.addProcessTime();
        
        cv::imshow("Performance Test", frame);
        monitor.addDisplayTime();
        
        // Показываем прогресс каждые 10 кадров
        if ((i + 1) % 10 == 0) {
            std::cout << "Processed " << (i + 1) << "/" << frames_to_process << " frames" << std::endl;
        }
        
        if (cv::waitKey(1) == 27) break; // ESC для досрочного выхода
    }
    
    monitor.printStatistics();
    
    capture.release();
    cv::destroyAllWindows();
    return 0;
}