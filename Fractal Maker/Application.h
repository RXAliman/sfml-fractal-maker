#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <sstream>
#include <string>

const int n_vertices = 3;

class Application {
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;
    //objects
    sf::Vector2f m_pt[n_vertices]; //n Major Points
    sf::Vector2f c_pt;
    std::vector<sf::CircleShape> r_point;
    sf::CircleShape point;
    //logics
    sf::Mouse m_pos;
    sf::Color bg;
    bool canPress;
    int n;
    const int max_point = 10000;
    //text
    sf::Text i;
    sf::Text i2;
    sf::Text i3;
    sf::Text i4;
    //resources
    sf::Font f;
    //functions
    void initWindows();
    void initVariables();
public:
    Application();
    void pollEvents();
    void update();
    void updateInput();
    void updateDots();
    void render();
    const sf::RenderWindow* getWindow() const;
    ~Application();
};
