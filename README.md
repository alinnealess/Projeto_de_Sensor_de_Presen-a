# Projeto de IoT - Medição de Distância com ESP32 e Sensores HC-SR04 para Adafruit IO
Este projeto implementa um sistema de Internet das Coisas (IoT) usando um microcontrolador ESP32 para medir a distância com dois sensores de ultrassom HC-SR04 e publicar os dados no serviço Adafruit IO por meio do protocolo MQTT.

## Componentes Necessários:
1. ESP32
2. Sensores de Ultrassom HC-SR04 (2 unidades)
3. Fios de conexão
4. Acesso à Internet

## Configuração do Ambiente de Desenvolvimento:

1. Instalação do ESP32 na Arduino IDE:
- Certifique-se de ter o suporte ao ESP32 instalado na sua Arduino IDE. Siga as instruções em ESP32 Arduino Core para realizar a instalação.
2. Instalação da Biblioteca HC-SR04:
- Baixe e instale a biblioteca "NewPing" para o sensor HC-SR04 diretamente do Gerenciador de Bibliotecas da Arduino IDE.

## Conexão de Hardware:
1. Conectar Sensores HC-SR04:
2. Conecte os pinos VCC e GND dos sensores HC-SR04 ao ESP32.
3. Conecte os pinos de Trigger e Echo dos sensores HC-SR04 aos pinos especificados no código (trigPinS1, echoPinS1, trigPinS2, echoPinS2).

## Configuração do Código:
1. Definir Credenciais Wi-Fi e Adafruit IO:
- Modifique as variáveis wifi_ssid, wifi_password, mqtt_usernameAdafruitIO, e mqtt_keyAdafruitIO com suas credenciais.
2.Configurar Tópicos MQTT e Chaves Adafruit IO:
- Ajuste os tópicos MQTT para refletir seus feeds específicos no Adafruit IO.

## Execução do Projeto:
1. Carregamento do Código:
- Conecte o ESP32 ao computador via USB e carregue o código usando a Arduino IDE.
2. Monitor Serial:
- Abra o Monitor Serial no Arduino IDE (Ferramentas -> Monitor Serial) para visualizar a saída e depurar o código.
3. Adafruit IO:
- Acesse Adafruit IO para visualizar e monitorar os dados de distância dos sensores HC-SR04.
## Avisos:
Mantenha as credenciais (Wi-Fi, Adafruit IO) seguras e não as compartilhe publicamente.
Certifique-se de que os sensores HC-SR04 estejam corretamente conectados.
##Contribuição e Licença:
Sinta-se à vontade para contribuir, relatar problemas ou fazer melhorias neste projeto. O código está sob a Licença MIT.

## Autor:
Alinne Alessandra
