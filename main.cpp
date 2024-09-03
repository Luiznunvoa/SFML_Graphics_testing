#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

static sf::Text SetFont(sf::Font& font)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    text.setString("NULL");
    return text;
}

void UpdateRectanglePosition(sf::RectangleShape& rectangle, sf::Vector2f& increment, const sf::RenderWindow& window, const sf::Vector2u& size)
{
    if((rectangle.getPosition().x + size.x > window.getSize().x && increment.x > 0) ||
       (rectangle.getPosition().x < 0 && increment.x < 0))
    {
        // Reverse the direction on X axis.
        increment.x = -increment.x;
    }
    if((rectangle.getPosition().y + size.y > window.getSize().y && increment.y > 0) ||
       (rectangle.getPosition().y < 0 && increment.y < 0))
    {
        // Reverse the direction on Y axis.
        increment.y = -increment.y;
    }

    rectangle.setPosition(rectangle.getPosition() + increment);
}

static void UpedateFPSCount(sf::Text& fpsText, sf::Clock& clock, sf::Time& previousTime, float& frames)
{
    sf::Time currentTime = clock.getElapsedTime();
    sf::Time elapsedTime = currentTime - previousTime;

    if (elapsedTime.asSeconds() >= 1.0f)
    {
        float fps = frames / elapsedTime.asSeconds();
        fps = roundf(fps);
        std::string fpstext = std::to_string(fps);

        for(int i = 0; i < fpstext.length(); i++)
        {
            if(fpstext[i] == '.')
            {
                fpstext.erase(i);
            }
        }

        fpstext += " FPS";
        fpsText.setString(fpstext);

        frames = 0;
        previousTime = currentTime;
    }
}

int main()
{
    // Renderização da janela
    sf::RenderWindow window(sf::VideoMode(640, 480), "My window");

    // Limitar o FPS a 60
    window.setFramerateLimit(60);

    // Carrega a fonte
    sf::Font Arial;
    if (!Arial.loadFromFile("arial.ttf"))
    {
        return -1;
    }

    // Inicializa uma variável pro texto e define uma fonte
    sf::Text Fps = SetFont(Arial);

    // Inicializando quadrado
    sf::RectangleShape rectangle(sf::Vector2f(50.0f, 50.0f));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(320, 240);
    sf::Vector2f increment(2.0f, 2.0f);
    sf::Vector2u size = {50, 50};

    // Inicializa a variável para os eventos
    sf::Event event;

    // Definindo temporizador para cálculo do FPS
    sf::Clock clock;
    sf::Time previousTime = sf::Time::Zero;
    float frames = 0;

    while (window.isOpen())
    {
        // Recebe Inputs do usuário

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update do mundo

        UpdateRectanglePosition(rectangle, increment, window, size);

        UpedateFPSCount(Fps, clock, previousTime, frames);

        // Desenha o mundo
        window.clear(sf::Color::Green);

        window.draw(Fps);

        window.draw(rectangle);

        window.display();

        // Repete
        frames++;
    }

    return 0;
}
