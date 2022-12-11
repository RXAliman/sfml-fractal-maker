#include "Application.h"

Application::Application() {
    initVariables();
    initWindows();
}

//ACCESSORS
const sf::RenderWindow* Application::getWindow() const {
    return this->window;
}

//PRIVATE FUNCTIONS
void Application::initVariables() {
    this->f.loadFromFile("resources/centurygothic.ttf");

    this->i.setFont(this->f);
    this->i.setFillColor(sf::Color::Black);
    this->i.setPosition(sf::Vector2f(15.f,10.f));
    this->i.setScale(sf::Vector2f(1.f,1.f));
    std::stringstream ss1;
    ss1 << "Select " << n_vertices << " Points";
    this->i.setString(ss1.str());

    this->i2.setFont(this->f);
    this->i2.setFillColor(sf::Color::Black);
    this->i2.setPosition(sf::Vector2f(15.f,10.f));
    this->i2.setScale(sf::Vector2f(1.f,1.f));
    this->i2.setString("Select a Point");

    this->i3.setFont(this->f);
    this->i3.setFillColor(sf::Color::Black);
    this->i3.setPosition(sf::Vector2f(15.f,10.f));
    this->i3.setScale(sf::Vector2f(1.f,1.f));

    this->i4.setFont(this->f);
    this->i4.setFillColor(sf::Color::Black);
    this->i4.setPosition(sf::Vector2f(15.f,10.f));
    this->i4.setScale(sf::Vector2f(1.f,1.f));
    this->i4.setString("Done\n\nPress space to reset...");

    this->bg = sf::Color::White;

    this->n = 0;

    this->point.setRadius(1.f);
}
void Application::initWindows() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(videoMode, "Fractal Maker", sf::Style::Close | sf::Style::Titlebar);

    this->window->setFramerateLimit(60);
}

//PUBLIC FUNCTIONS
void Application::update()
{
    this->pollEvents();
    if (this->n <= n_vertices) this->updateInput();
    else if (this->n < max_point) this->updateDots();
}
void Application::updateInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->canPress && this->window->hasFocus())
    {
        if (this->n < n_vertices)
        {
            this->point.setFillColor(sf::Color::Red);
            this->point.setPosition(sf::Vector2f(this->m_pos.getPosition(*this->window)));

            this->m_pt[n] = sf::Vector2f(this->m_pos.getPosition(*this->window));

            this->r_point.push_back(this->point);
        }
        else if (this->n == n_vertices)
        {
            this->point.setFillColor(sf::Color::Blue);
            this->point.setPosition(sf::Vector2f(this->m_pos.getPosition(*this->window)));

            this->c_pt = sf::Vector2f(this->m_pos.getPosition(*this->window));

            this->r_point.push_back(this->point);
        }
        this->n++;
        this->canPress = false;
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        this->canPress = true;
}
void Application::updateDots()
{
    int ra = rand()%n_vertices;
    //static int prev_ra = -1;

    //while (prev_ra == ra) ra = rand()%n_vertices;

    this->point.setFillColor(sf::Color::Black);
    this->point.setPosition((this->c_pt.x+this->m_pt[ra].x)/2,(this->c_pt.y+this->m_pt[ra].y)/2);

    //prev_ra = ra;

    this->c_pt = this->point.getPosition();

    this->r_point.push_back(this->point);

    std::stringstream ss;
    ss << "Creating Fractal...\n\nPoints: " << ++n;
    this->i3.setString(ss.str());
}
void Application::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape) this->window->close();
            if (this->event.key.code == sf::Keyboard::Space) {
                this->r_point.clear();
                this->n = 0;
            }
            break;
        default:
            break;
        }
    }
}
void Application::render()
{
    this->window->clear(this->bg);
    //draw objects
    if (this->n < n_vertices) this->window->draw(this->i);
    else if (this->n == n_vertices) this->window->draw(this->i2);
    else if (this->n < max_point) this->window->draw(this->i3);
    else this->window->draw(this->i4);
    for (auto &p : this->r_point)
    {
        this->window->draw(p);
    }

    this->window->display();
}

Application::~Application() {
    delete this->window;
}

