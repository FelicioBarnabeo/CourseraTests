#include "stats.h"
#include <iostream>

//Представим, что у нас есть web-сервер, который обслуживает запросы к интернет-магазину. Он поддерживает следующий набор запросов по протоколу HTTP:

//GET / HTTP/1.1 — получить главную страницу магазина
//POST /order HTTP/1.1 — разместить новый заказ
//POST /product HTTP/1.1 — добавить новый товар в магазин (команда админки)
//GET /order HTTP/1.1 — получить детали заказа
//PUT /product HTTP/1.1 — то же самое, что и POST /order HTTP/1.1
//GET /basket HTTP/1.1 — получить состав текущей корзины клиента
//DELETE /product HTTP/1.1 — удалить товар из интернет-магазина (команда админки)
//GET /help HTTP/1.1 — получить страницу о том, как пользоваться интернет-магазином
//С точки зрения протокола HTTP, первые части приведённых выше запросов («GET», «POST», «PUT», «DELETE») называются методами.
//Вторые части называются URI (Uniform Resource Identifier). Третья часть — это версия протокола.
//Таким образом, наш web-сервер поддерживает 4 метода: GET, POST, PUT, DELETE и 5 URI: «/», «/order», «/product», «/basket», «/help».

//Главный системный администратор нашего сервера озаботился его масштабированием и для начала он решил изучить статистику использования.
//Он хочет для каждого метода и каждого URI посчитать, сколько раз он встречался в запросах к серверу за последний месяц. Он попросил вас помочь с этим.

//Вам нужно, основываясь на реализации функции ServeRequests, реализовать класс Stats и функцию ParseRequest. Дополнительные требования к классу Stats:

//метод GetMethodStats возвращает словарь, в котором для каждого метода хранится, сколько раз он встретился в качестве аргумента метода AddMethod;
//метод GetUriStats работает аналогично для URI;
//если метод, переданный в метод AddMethod, не поддерживается нашим сервером (список поддерживаемых методов приведён выше),
//то нужно на единицу увеличить счётчик для метода «UNKNOWN» (подробнее см. юнит-тесты в заготовке решения);
//если URI, переданный в метод AddUri, не поддерживается нашим сервером, то нужно на единицу увеличить счётчик для URI «unknown».

void Trim(string_view& str)
{
    size_t trims = str.find_first_not_of(" ");
    str.remove_prefix(trims);
}

string_view ReadToken(string_view& str)
{
    Trim(str);
    size_t pos = str.find(' ');
    auto result = str.substr(0,pos);
    str.remove_prefix(pos!=str.npos ? pos+1 : str.size());
    return result;
}

HttpRequest ParseRequest(string_view line)
{
    auto method = ReadToken(line);
    auto uri = ReadToken(line);
    auto protocol = ReadToken(line);
    //cout<<method<<" "<<uri<<" "<<protocol<<endl;
    return {method,uri,protocol};
}

Stats::Stats()
{
    methodStats = {{"GET",0}, {"POST",0}, {"PUT",0}, {"DELETE",0}, {"UNKNOWN",0}};
    uriStats = {{"/",0},{"/order",0},{"/product",0},{"/basket",0},{"/help",0},{"unknown",0}};
}

void Stats::AddMethod(string_view method)
{
    //cout<<"Add Method "<<method;
    if(auto it=methodStats.find(method); it!=methodStats.end()){
        it->second++;
    }else{
        methodStats["UNKNOWN"]++;
    }
}

void Stats::AddUri(string_view uri)
{
    if(auto it=uriStats.find(uri); it!=uriStats.end()){
        it->second++;
    }else{
        uriStats["unknown"]++;
    }
}

const map<string_view, int> &Stats::GetMethodStats() const
{
    return methodStats;
}

const map<string_view, int> &Stats::GetUriStats() const
{
    return uriStats;
}
