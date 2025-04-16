# 基于esp32c3与mqtt的远程唤醒
## 使用方法
1. 确保你的计算机能够被远程唤醒（可能需要关闭windows快速启动，详情请见：https://learn.microsoft.com/en-us/troubleshoot/windows-client/setup-upgrade-and-drivers/wake-on-lan-feature）
2. 申请一个mqtt服务器，记录服务器域名、端口、用户名、密码、根证书
3. 打开`config_default.cpp`，依次填写，请注意不同设备的`mqtt_client_id`不能重复，mqtt服务器认为`mqtt_client_id`是唯一的
4. 将`config_default.cpp`重命名为`config.cpp`并移动到`src`下
5. 注意`src/main.cpp`中`LED_BUILDIN`应修改为你的开发板上的build-in led，我的开发板是esp32 supermini开发板
6. 使用`vscode`打开项目，并安装`PlatformIO IDE`扩展，进行烧录

## 通信协议
1. 默认使用话题`wake`，qos为0
2. 检查设备在线状态
    主机发送`{"id":0,"msg":0,"time":(当前utc时间戳)}`
    `device_id=0`的设备回复`{"id":0,"msg":1,"time":(当前utc时间戳)}`
3. 唤醒设备
    主机发送`{"id":0,"msg":2,"time":(当前utc时间戳)}`
    `device_id=0`的设备会尝试唤醒`wake_device_MAC`对应的设备，不会回复
4. 如需自定义请修改`src/mqtt_connect.cpp`