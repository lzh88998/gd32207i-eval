# GD23207I-EVAL Board FreeRTOS + AWS IoT Reference Integration

This is based on 202007 FreeRTOS + TCP with mbedtls and coreMQTT porting to create a demo for connecting to AWS IoT Core

Button event will send to AWS MQTT topics

User can send AWS MQTT message to contol LED on the board with following message format：

Topic：{ThingName}\led
Message: {LED_index} {0|1}
For example: 1 1 will turn the LED 1 on, and 1 0 will turn LED 1 off
