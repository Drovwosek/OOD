#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CShapeDecorator.h"

sf::Vector2f extractCoordinates(const std::string& str);
void ReadShapesFromFile(const std::string& fileName, std::vector<std::unique_ptr<CBaseShape>>& shapes);
void WriteShapesToFile(const std::string& fileName, const std::vector<std::unique_ptr<CBaseShape>>& shapes);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Shapes");
    std::vector<std::unique_ptr<CBaseShape>> shapes;

    ReadShapesFromFile("input.txt", shapes);

    WriteShapesToFile("output.txt", shapes);


    // Создаем новый вектор для декорированных фигур
    std::vector<std::shared_ptr<CBaseShape>> decoratedShapes;

    // Создаем декоратор для обводки (например, красный цвет)
    sf::Color borderColor = sf::Color::Yellow;

    // Проходим по исходному вектору и создаем декорированные версии фигур
    for (auto& shape : shapes)
    {
        // Создаем декорированный объект для каждой фигуры
        std::shared_ptr<CBaseShape> decoratedShape = std::make_shared<CShapeDecorator>(std::move(shape), borderColor);

        // Добавляем декорированную фигуру в новый вектор
        decoratedShapes.push_back(decoratedShape);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (const auto& shape : decoratedShapes)
        {
            shape->Draw(window);
        }



        window.display();
    }


    return 0;
}

sf::Vector2f extractCoordinates(const std::string& input) {

    sf::Vector2f result;

    // Ищем индекс начала координат (после знака равно)
    size_t equalSignPos = input.find('=');
    if (equalSignPos == std::string::npos) {
        std::cerr << "Ошибка: не найден знак равно в строке." << std::endl;
        return result; // Возвращаем пустой вектор
    }

    // Ищем индекс конца координат (после точки с запятой)
    size_t semicolonPos = input.find(';', equalSignPos);
    if (semicolonPos == std::string::npos) {
        std::cerr << "Ошибка: не найдена точка с запятой в строке." << std::endl;
        return result; // Возвращаем пустой вектор
    }

    // Извлекаем подстроку, содержащую координаты
    std::string coordinatesStr = input.substr(equalSignPos + 1, semicolonPos - equalSignPos - 1);

    // Используем stringstream для парсинга координат
    std::stringstream ss(coordinatesStr);
    char comma; // Для разделителя ","

    if (!(ss >> result.x >> comma >> result.y)) {
        std::cerr << "Ошибка: неверный формат координат." << std::endl;
        result = sf::Vector2f(); // Возвращаем пустой вектор
    }

    return result;
}

void ReadShapesFromFile(const std::string& fileName, std::vector<std::unique_ptr<CBaseShape>>& shapes)
{
    std::ifstream input(fileName);

    std::string line;
    while (std::getline(input, line))
    {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "CIRCLE:")
        {
            sf::Vector2f center;
            float radius;

            std::string centerStr, radiusStr;
            iss >> centerStr >> radiusStr;

            center = extractCoordinates(centerStr);

            size_t radiusPos = radiusStr.find('=');
            if (radiusPos != std::string::npos)
                radius = std::stof(radiusStr.substr(radiusPos + 1));

            shapes.push_back(std::make_unique<CCircleShape>(center, radius));
        }
        if (type == "TRIANGLE:")
        {
            sf::Vector2f p1, p2, p3;

            std::string p1Str, p2Str, p3Str;
            iss >> p1Str >> p2Str >> p3Str;

            p1 = extractCoordinates(p1Str);
            p2 = extractCoordinates(p2Str);
            p3 = extractCoordinates(p3Str);

            shapes.push_back(std::make_unique<CTriangleShape>(p1, p2, p3));
        }
        if (type == "RECTANGLE:")
        {
            sf::Vector2f p1, p2;

            std::string p1Str, p2Str;
            iss >> p1Str >> p2Str;

            p1 = extractCoordinates(p1Str);
            p2 = extractCoordinates(p2Str);

            shapes.push_back(std::make_unique<CRectangleShape>(p1, p2));
        }
    }
}

void WriteShapesToFile(const std::string& fileName, const std::vector<std::unique_ptr<CBaseShape>>& shapes)
{
    std::ofstream output(fileName);
    for (const auto& shape : shapes)
    {
        output << shape->ToString() << std::endl;
    }
}
