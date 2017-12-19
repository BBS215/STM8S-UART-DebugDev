# STM8S-UART-DebugDev

Проект предназначен для управления МК STM8S через UART. UART подключается к пинам PD5 (UART1_TX) и PD6 (UART1_RX). Кварц не требуется.
Согласование уровней напряжений UART обязательно!

МК - STM8S003F3P6

Среда разработки - STVD 4.3.11

Компилятор - Cosmic cross compiler v.4.4.7

ПО для управления: 
- https://github.com/BBS215/STM8S-UART-DebugTool - консольная утилита
- https://github.com/BBS215/STM8S-UART-DebugToolGUI - графическая утилита
