# Controle de Servo Motor com Raspberry Pi Pico (PWM)  

## Descrição  
Este projeto utiliza o **Raspberry Pi Pico (RP2040)** para controlar um **servo motor** por meio de um sinal **PWM (Pulse Width Modulation)**. O código gera um sinal PWM de **50 Hz** e ajusta o **duty cycle** para movimentar o servo em diferentes posições.  

### Funcionamento  
1. **Inicialização do PWM:**  
   - O **pino GPIO 22** é configurado como saída PWM.  
   - O **divisor de clock** e o **período PWM** são ajustados para gerar **50 Hz**, a frequência típica de controle de servos.  
2. **Movimentos iniciais do servo:**  
   - O servo motor passa por **três posições pré-definidas** durante a inicialização.  
   - Cada posição corresponde a um **duty cycle específico** do PWM.  
3. **Movimentação contínua do servo:**  
   - Após a inicialização, o servo **oscila continuamente** entre duas posições, ajustando o **duty cycle** gradualmente.  
   - O movimento ocorre em **passos de 2,5 unidades**, garantindo transições suaves.  
4. **Monitoramento via Terminal USB:**  
   - O código exibe mensagens indicando o **duty cycle** e a direção do movimento (**up/down**).  

## Especificações Técnicas  
- **Frequência do PWM:** **50 Hz** (período de **20 ms**)  
- **Duty cycle ajustável:** Varia de **2,5% a 12%** para controlar a posição do servo  
- **Resolução do PWM:** Baseada no valor de contagem de **9999**  
- **Pino de controle do servo:** **GPIO 22**

  ### Aluno
**Andrei Luiz da Silva Rodrigues**

### Matrícula
**TIC370100444**

### Link do video apresentando o projeto:
https://www.youtube.com/watch?si=bK9tC_N6PCI1Wj2H&v=8UMlDcmbeFE&feature=youtu.be
