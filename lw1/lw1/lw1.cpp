#include <SFML/Graphics.hpp>

#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CShapeDecorator.h"

sf::Vector2f extractCoordinates(const std::string& str);
void ReadShapesFromFile(const std::string& fileName, std::vector<std::unique_ptr<CBaseShape>>& shapes);
void WriteShapesToFile(const std::string& fileName, const std::vector<std::unique_ptr<CBaseShape>>& shapes);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "");

    std::vector<std::unique_ptr<CBaseShape>> shapes;

    ReadShapesFromFile("input.txt", shapes);
    WriteShapesToFile("output.txt", shapes);

    std::vector<std::shared_ptr<CBaseShape>> decoratedShapes;

    // Проходим по исходному вектору и создаем декорированные версии фигур
    for (auto& shape : shapes)
    {
        // Создаем декорированный объект для каждой фигуры
        std::shared_ptr<CBaseShape> decoratedShape = std::make_shared<CShapeDecorator>(std::move(shape));

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

sf::Vector2f extractCoordinates(const std::string& input) 
{

    sf::Vector2f result;

    size_t beginCoordinatesSection = input.find('=');
    if (beginCoordinatesSection == std::string::npos) {
        std::cerr << "Warning: equalSign not found in string." << std::endl;
        return result;
    }

    size_t endCoordinatesSection = input.find(';', beginCoordinatesSection);
    if (endCoordinatesSection == std::string::npos) {
        std::cerr << "Warning: semicolonSign not found in string." << std::endl;
        return result; 
    }

    std::string coordinatesStr = input.substr(beginCoordinatesSection + 1, endCoordinatesSection - beginCoordinatesSection - 1);

    std::stringstream ss(coordinatesStr);
    char separator;

    if (!(ss >> result.x >> separator >> result.y)) {
        std::cerr << "Warning: invalid format of coordinates." << std::endl;
        result = sf::Vector2f(); 
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
