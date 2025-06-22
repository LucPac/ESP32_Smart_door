<div align="center">
  <h1>🚪✨ Cửa thông minh dùng ESP32 và Blynk ✨🚪</h1>
  <p>
    <img src="https://img.shields.io/badge/Vi%20%C4%91i%E1%BB%83u%20khi%E1%BB%83n-ESP32-blueviolet?style=for-the-badge&logo=espressif&logoColor=white" alt="ESP32 Badge">
    <img src="https://img.shields.io/badge/N%E1%BB%81n%20t%E1%BA%A3ng-Blynk-brightgreen?style=for-the-badge&logo=blynk&logoColor=white" alt="Blynk Badge">
    <img src="https://img.shields.io/badge/Ng%C3%B4n%20ng%E1%BB%AF-C%2B%2B-blue?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++ Badge">
  </p>

  ---

  <p>
    <a href="#🚀-tổng-quan">Tổng quan</a> •
    <a href="#🛠️-hướng-dẫn-cài-đặt-và-sử-dụng">Hướng dẫn cài đặt và sử dụng</a> •
    <a href="#⚙️-cấu-hình-blynk">Cấu hình Blynk</a> •
    <a href="#🚩-sản-phẩm-thực-tế">Sản phẩm thực tế</a>
  </p>

  ---
</div>

<br>

## 🚀 Tổng quan

Chào mừng bạn đến với kho lưu trữ **`ESP32_Smart_door`**!

Dự án này cung cấp một giải pháp hoàn chỉnh cho việc xây dựng một hệ thống cửa thông minh, cho phép bạn điều khiển đóng/mở và giám sát trạng thái của cửa từ bất cứ đâu thông qua ứng dụng di động Blynk. Sử dụng vi điều khiển ESP32 mạnh mẽ, dự án này là sự kết hợp giữa phần cứng và phần mềm để mang lại sự tiện lợi và an toàn cho ngôi nhà của bạn.

<br>

## 🛠️ Hướng dẫn cài đặt và sử dụng

Để triển khai dự án này, bạn cần có các phần mềm và thành phần phần cứng sau:

### Yêu cầu phần mềm:
* VS Code
* PlatformIO IDE Extension
* Ứng dụng Blynk (Android/iOS)

### Yêu cầu phần cứng:
* ESP32
* Servo SG90 (Mô phỏng cửa)
* Ma trận phím 4x4
* Breadboard, dây cắm hoặc vẽ PCB và hàn mạch

### Các bước cơ bản:

* Cài đặt VS Code và PlatformIO IDE Extension
* Clone hoặc tải về
    ```bash
    git clone https://github.com/your-username/ESP32_Smart_door.git
    ```
* Mở dự án trong VS Code với PlatformIO
* Cấu hình thông tin Blynk và Wifi (xem phần dưới).
* Biên dịch và Upload mã nguồn
* Thiết lập ứng dụng Blynk
* Kết nối phần cứng

   ![Image](https://github.com/user-attachments/assets/11b66dff-b35e-4c9a-ab23-a85c969d9280)
<br>

## ⚙️ Cấu hình Blynk

Để dự án hoạt động, bạn cần cấu hình tài khoản và dự án Blynk của mình.

### 1. Tạo dự án mới trên Blynk Console
* Truy cập [Blynk Console](https://blynk.cloud/) và tạo một tài khoản (nếu chưa có).
* Tạo một **New Template** cho dự án "Smart Door".
* Ghi lại **Template ID** và **Template Name**.
* Khi tạo thiết bị mới từ Template này, bạn sẽ nhận được một **Auth Token**.

### 2. Cập nhật thông tin vào mã nguồn
Trong file `src/main.cpp`, bạn cần thay thế các placeholder sau bằng thông tin của mình:
* Nhập thông tin trên Blynk của bạn vào khoảng trống.
* Tiếp theo nhập tên và mật khẩu Wifi.
```cpp
#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_DEVICE_NAME "YOUR_BLYNK_TEMPLATE_NAME" // Tên thiết bị của bạn
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

char ssid[] = "YOUR_WIFI_SSID";     // Tên mạng Wifi của bạn
char pass[] = "YOUR_WIFI_PASSWORD"; // Mật khẩu Wifi của bạn
```

### 3. Thiết lập Datastreams trên ứng dụng Blynk
* Thiết lập công tắc ảo Control Pass để điều khiển việc cho phép và không cho phép nhập mật khẩu.
* Thiết lập công tắc ảo Control Door để đóng mở cửa từ xa.
* Bạn cần tạo các Datastreams tương ứng trên ứng dụng Blynk để điều khiển và giám sát cửa

**Control Door**: Dùng cho điều khiển đóng/mở cửa.  
**Control Pass**: Dùng để điều khiển việc cho phép và không cho phép nhập mật khẩu.

![Image](https://github.com/user-attachments/assets/fcbd7521-018a-412e-ab2a-13345259e6de)

### 4. Thiết lập Events & Notifications trên Blynk
* Thiết lập để nhận thông báo khi cửa mở và khi nhập sai mật khẩu quá nhiều lần.
  
**door_warning**: Nhận thông báo khi cửa mở.  
**infor_log**: Nhận thông báo khi nhập sai mật khẩu quá nhiều lần.

![Image](https://github.com/user-attachments/assets/4ab1b57e-5ace-4121-b9c9-64a33b7e6cba)
<br>

## 🚩 Sản phẩm thực tế  

* PCB

![image](https://github.com/user-attachments/assets/ea0833b8-a924-4761-8587-1a2b40b48489)

* Hình ảnh sản phẩm  
  
![Image](https://github.com/user-attachments/assets/4d81e4d7-fea2-4c3e-aadd-f5422bfd31a5)  

![Image](https://github.com/user-attachments/assets/b90fe5ab-9323-43b3-8db6-f412df51777b)  

![Image](https://github.com/user-attachments/assets/1ec14359-2239-489c-9ed6-a1922a23d178)  

* Video chạy thử sản phẩm  

[![Image](https://github.com/user-attachments/assets/3ac83cd1-7f86-4c51-a952-ec393e816f73)](https://youtu.be/4SuPDmZ4MYU)

<br>

---

<div align="center">
  <br>
  <p>Cảm ơn bạn đã ghé thăm! Hy vọng repo này hữu ích cho việc học tập và nghiên cứu của bạn. 😊</p>
  </div>
