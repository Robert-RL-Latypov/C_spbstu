#include<stdio.h>
#include<stdlib.h>
#include <math.h>

const int year_now = 2024, // Текущий год
age = 30, //Количество лет
year_end = year_now + age, //Год окончания наблюдений
month_now = year_now*12,
month_end = year_end*12;
const float indexing = 12, //Индексация и инфляция
start_capital = 2000000, //Изначальный капитал
apartament_cost = 20000000, //Стоимость квартиры
i_percent = 18,
month_i_percent = i_percent/12, //Годовой процент по ипотеке
v_percent = 16, //Процент по вкладу
month_v_percent = v_percent/12,
month_salary = 150000, //Зарплата
month_food = 15000, //Затраты на еду в месяц
month_rent = 25000; //Аренда за квартиру в месяц


struct person
{
    int 
    year,
    month;
    float
    flat_cost,
    credit, //Сумма кредита
    salary, 
    food, 
    rent, 
    ostatok, //Сумма, оставшаяся от зарплаты после вычета затрат
    capital; //Накопленная сумма за весь промежуток врем
};


//Повышение зарплаты за счет индексации и затрат за счет инфляции
float increase (float a, float b){
    return a*(1+b/100);
}

//Подсчет капитала Алисы
float Alice() { 
    struct person Alice;
    Alice.year = year_now;
    Alice.flat_cost = apartament_cost;
    Alice.credit = Alice.flat_cost - start_capital;
    Alice.salary = month_salary;
    Alice.food = month_food;
    Alice.capital = 0;
    Alice.ostatok = 0;
    Alice.month = month_now;
   
   //Когда кредит будет меньше или равен нулю, цикл остановиться
    while (Alice.month <= month_end){
        for (int i = 1; Alice.credit > 0 && i<=12; i++, Alice.month++)
            {
                Alice.credit = increase(Alice.credit, month_i_percent);
                Alice.ostatok = Alice.salary - Alice.food;
                Alice.credit -= Alice.ostatok;
            }
        if ( Alice.credit > 0)
        {
            Alice.salary = increase(Alice.salary, indexing);
            Alice.food = increase(Alice.food, indexing);
        }
        else {
            break;
        }
    }
    Alice.capital = Alice.credit*(-1); //Так как кредит получился меньше нуля, чего не может быть, то эти деньги уходят в капитал

    //Начисление средств в капитал после выплаты кредита
    while (Alice.month <= month_end) {
        for (int i = 1; i <= 12; i++, Alice.month++)
        {
            Alice.ostatok = Alice.salary - Alice.food;
            Alice.capital += Alice.ostatok;
        }
        Alice.salary = increase(Alice.salary, indexing);
        Alice.food = increase(Alice.food, indexing);
    
    }
    return Alice.capital;
}

//Подсчет капитала Боба
float Bob(){
    struct person Bob;
    Bob.year = year_now;
    Bob.flat_cost = apartament_cost;
    Bob.salary = month_salary;
    Bob.food = month_food;
    Bob.rent = month_rent;
    Bob.capital = start_capital;
    Bob.ostatok = 0;
    Bob.month = month_now;
    
    
   //Когда капитал превысит стоимость квартиры, цикл остановиться
    while (Bob.month <= month_end) {
        for (int i = 1; Bob.flat_cost > Bob.capital && i<=12; i++, Bob.month++)
            {
                Bob.ostatok = Bob.salary - Bob.food - Bob.rent;
                Bob.capital += Bob.ostatok;
            }
        if (Bob.flat_cost > Bob.capital)
        {
            Bob.capital = increase(Bob.capital, v_percent);
            Bob.salary = increase(Bob.salary, indexing);
            Bob.food = increase(Bob.food, indexing);
            Bob.rent = increase(Bob.food, indexing);
            Bob.flat_cost = increase(Bob.flat_cost, indexing);
        }
        else {
            break;
        }
    }
    Bob.capital -= Bob.flat_cost; //Боб покупает квартиру
//Подсчет капитала с исключением затрат на аренду
    while (Bob.month <= month_end) {
        for (int i = 1; i <= 12; i++, Bob.month++)
        {
            Bob.ostatok = Bob.salary - Bob.food;
            Bob.capital += Bob.ostatok;
        }
        Bob.salary = increase(Bob.salary, indexing);
        Bob.food = increase(Bob.food, indexing);
    }
    return Bob.capital;  
}


int main() 
{
    printf("Alice capital %f\n", Alice());
    printf("Bob capital %f\n", Bob());
    if (Alice() > Bob())
    {
        printf("Alice win\n");
        
    }
    else
    {
        printf("Bob win\n");
        
    }
    system("pause");

}