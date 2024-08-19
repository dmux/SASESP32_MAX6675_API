# SASESP32_MAX6675_API

## Descrição

O projeto **SASESP32_MAX6675_API** é uma aplicação desenvolvida para o microcontrolador ESP32, utilizando o sensor de temperatura MAX6675. O projeto permite a comunicação do ESP32 com um servidor através de uma API REST, enviando dados coletados pelo sensor. Além disso, o projeto inclui um servidor web integrado, que permite a atualização do firmware via OTA (Over-the-Air) através de uma interface web segura.

## Funcionalidades

- **Leitura de temperatura**: Utiliza o sensor MAX6675 para coletar dados de temperatura em graus Celsius e Fahrenheit.
- **Comunicação via API**: Envia os dados coletados para um servidor remoto através de requisições HTTPS.
- **Servidor web embutido**: Fornece uma interface para realizar a atualização do firmware do ESP32 de forma remota e segura.
- **Autenticação básica**: Requer login e senha para acessar a interface de atualização de firmware.

## Estrutura do Projeto

- **Wi-Fi**: Conexão à rede Wi-Fi configurada para permitir a comunicação com a internet.
- **Sensor MAX6675**: Configuração e leitura de temperatura do sensor.
- **Servidor Web**: Configuração de um servidor HTTP integrado para permitir a atualização OTA.
- **API REST**: Comunicação com o servidor remoto para envio dos dados de temperatura e informações do dispositivo.

## Dependências

Este projeto utiliza as seguintes bibliotecas:

- `WiFi.h`
- `WiFiClient.h`
- `WiFiClientSecure.h`
- `HTTPClient.h`
- `WebServer.h`
- `ESPmDNS.h`
- `Update.h`
- `ArduinoJson.h`
- `max6675.h`
- `EspHtmlTemplateProcessor.h`

## Configuração

### Variáveis de Configuração

- **Rede Wi-Fi**: 
  - `ssid`: Nome da rede Wi-Fi.
  - `password`: Senha da rede Wi-Fi.
- **Informações do dispositivo**:
  - `version`: Versão do firmware.
  - `deviceId`: Identificador único do dispositivo.
- **Configuração do sensor**:
  - `thermoDO`, `thermoCS`, `thermoCLK`: Pinos utilizados para comunicação com o sensor MAX6675.
- **Servidor API**:
  - `ca_cert`: Certificado de segurança do servidor remoto.

### Configuração do Ambiente

1. Conecte o ESP32 à rede Wi-Fi configurando as variáveis `ssid` e `password` no código.
2. Verifique a conexão com o servidor remoto utilizando o certificado CA fornecido.
3. Configure os pinos do sensor MAX6675 conforme necessário.

## Instruções de Uso

1. **Compilação e Upload**: Compile o código e faça o upload para o ESP32 usando o Arduino IDE.
2. **Conexão Wi-Fi**: O ESP32 tentará se conectar à rede Wi-Fi configurada. Certifique-se de que a rede esteja disponível.
3. **Acesso ao Servidor Web**: Acesse o endereço IP do ESP32 através de um navegador web para acessar a interface de atualização OTA.
4. **Envio de Dados para o Servidor**: Os dados de temperatura serão coletados e enviados automaticamente ao servidor configurado a cada minuto.

## Considerações

- O código atual permite a coleta de temperatura a cada minuto, mas isso pode ser ajustado conforme necessário.
- A comunicação com o servidor utiliza HTTPS para garantir a segurança dos dados transmitidos.
