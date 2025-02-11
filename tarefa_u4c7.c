#include <stdio.h>           // Biblioteca padrão para entrada e saída de dados
#include "pico/stdlib.h"     // Biblioteca do Raspberry Pi Pico para controle de GPIO e temporização
#include "hardware/pwm.h"    // Biblioteca para controle do hardware de PWM

// Definição do pino de controle do servo motor
#define PWM_SERVO 22 // Pino GPIO 22 será utilizado para gerar o sinal PWM para o servo

// Definição dos parâmetros do PWM
const uint16_t WRAP_PERIOD = 9999; // Contagem máxima do PWM para gerar 50 Hz (PWM para servo)
const float PWM_DIVISER = 250.0;   // Divisor do clock para alcançar a frequência de 50 Hz
const uint16_t SERVO_STEP = 2.5;   // Passo de incremento/decremento do duty cycle
uint16_t servo_level = 0;        // Nível inicial do PWM (posição inicial do servo)

// Função para configurar o PWM no pino do servo
void pwm_setup()
{
    gpio_set_function(PWM_SERVO, GPIO_FUNC_PWM);   // Configura o pino GPIO como saída PWM
    uint slice = pwm_gpio_to_slice_num(PWM_SERVO); // Obtém o slice do PWM correspondente ao pino

    pwm_set_clkdiv(slice, PWM_DIVISER); // Define o divisor de clock para 50 Hz
    pwm_set_wrap(slice, WRAP_PERIOD);   // Define o valor máximo de contagem do PWM

    pwm_set_gpio_level(PWM_SERVO, servo_level); // Define o ciclo de trabalho inicial do PWM
    pwm_set_enabled(slice, true);               // Habilita o PWM no slice correspondente
}

// Função para realizar os movimentos iniciais do servo motor
void movimentos_iniciais()
{
    // Move o servo para a posição correspondente a 12% do duty cycle (1200 contagens)
    pwm_set_gpio_level(PWM_SERVO, 1200);
    printf("Duty cycle: %d\n", 1200); // Exibe o duty cycle aplicado
    sleep_ms(5000);                   // Aguarda 5 segundos para estabilização

    // Move o servo para a posição correspondente a 7,35% do duty cycle (735 contagens)
    pwm_set_gpio_level(PWM_SERVO, 735);
    printf("Duty cycle: %d\n", 735);
    sleep_ms(5000);

    // Move o servo para a posição correspondente a 2,5% do duty cycle (250 contagens)
    pwm_set_gpio_level(PWM_SERVO, 250);
    printf("Duty cycle: %d\n", 250);
    sleep_ms(5000);
}

// Função principal
int main()
{
    stdio_init_all(); // Inicializa a comunicação serial (depuração)
    pwm_setup();      // Configura o PWM para o servo motor

    uint up_down = 1; // Variável de controle do sentido do duty cycle

    movimentos_iniciais(); // Executa a sequência de inicialização do servo

    // Loop infinito para controle contínuo do servo
    while (true)
    {
        pwm_set_gpio_level(PWM_SERVO, servo_level); // Atualiza o duty cycle do PWM

        if (up_down)
        {
            servo_level += SERVO_STEP; // Aumenta o duty cycle (move o servo para frente)
            if (servo_level >= 1200)   // Limite máximo (posição correspondente a 12%)
            {
                up_down = 0; // Inverte para diminuir o duty cycle
                printf("down\n"); // Exibe a direção do movimento
            }
        }
        else
        {
            servo_level -= SERVO_STEP; // Diminui o duty cycle (move o servo para trás)
            if (servo_level <= 200) // Limite mínimo de aproximadamente 0 graus (posição inicial do servo)
            {
                printf("up\n"); // Exibe a direção do movimento
                up_down = 1; // Inverte para aumentar o duty cycle
            }
        }
        sleep_ms(10); // Aguarda 10 ms antes da próxima atualização
    }
}
