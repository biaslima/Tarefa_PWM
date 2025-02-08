# Controle de Servomotor e LED RGB com PWM no Raspberry Pi Pico

## **Vídeo Demonstrativo**
Assista ao vídeo demonstrativo da solução no link abaixo:  
[Vídeo da Simulação](https://drive.google.com/file/d/1fvnZnNoNLVIjGGCf0FmUs1q6gM6PG73Z/view?usp=sharing)

---

## **Descrição do Projeto**
Este projeto implementa o controle de um **servomotor** e de um **LED RGB** utilizando o módulo PWM do microcontrolador RP2040 (Raspberry Pi Pico). A atividade foi realizada com base nos seguintes objetivos:

1. Configurar o PWM na GPIO 22 para controlar o servomotor com uma frequência de aproximadamente **50 Hz** (período de 20 ms).
2. Ajustar o ciclo ativo (duty cycle) para diferentes ângulos do servo:
   - **2400 µs** (~180°)
   - **1470 µs** (~90°)
   - **500 µs** (~0°)
3. Criar uma rotina para movimentação suave entre os ângulos de 0° e 180°, com incrementos de ±5 µs a cada 10 ms.
4. Utilizar a GPIO 12 para controlar o brilho do LED RGB, observando seu comportamento luminoso.

---

## **Como Executar o Projeto**

### **1. Pré-requisitos**
- Raspberry Pi Pico W.
- Ambiente de desenvolvimento configurado com o Pico SDK.
- Simulador Wokwi integrado ao VS Code.
- Ferramenta educacional BitDogLab para análise do LED RGB.

### **2. Configuração**
```sh
git clone https://github.com/biaslima/Tarefa_PWM.git
cd Tarefa_PWM
```

```sh
mkdir build && cd build
cmake ..
make
```

```sh
make flash
```

---

## **Resultados Esperados**

### **1. Controle do Servomotor**
- O servo se move para as posições desejadas (0°, 90°, e 180°) conforme os valores de largura de pulso configurados.
- A movimentação suave entre os ângulos é perceptível, com incrementos de ±5 µs.

### **2. Comportamento do LED RGB**
- O LED apresenta um efeito cíclico de aumento e diminuição do brilho.
- A curva quadrática aplicada ao duty cycle (`fade * fade`) torna as transições mais suaves e perceptíveis.
