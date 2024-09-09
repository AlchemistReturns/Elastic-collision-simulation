#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>

class Particle {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Particle(sf::Vector2f position) {
        sf::Uint8 radius = std::rand() % 5 + 1;
        shape.setRadius(radius);
        sf::Uint8 r = std::rand() % 256;
        sf::Uint8 g = std::rand() % 256;
        sf::Uint8 b = std::rand() % 256;
        shape.setFillColor(sf::Color(r, g, b));
        shape.setPosition(position);

        // Random direction
        velocity.x = (std::rand() % 100 - 50) / 50.0f;
        velocity.y = (std::rand() % 100 - 50) / 50.0f;
    }

    void update() {
        this->velocity.y += 0.05;
        shape.move(velocity);
    }

    void collide(Particle* p) {
        float r12 = this->shape.getRadius() * this->shape.getRadius();
        float r22 = (*p).shape.getRadius() * (*p).shape.getRadius();
        float u1x = this->velocity.x;
        float u2x = (*p).velocity.x;
        float u1y = this->velocity.y;
        float u2y = (*p).velocity.y;

        this->velocity.x = (r12 - r22) / (r12 + r22) * u1x + (2 * r22) / (r12 + r22) * u2x;
        this->velocity.y = (r12 - r22) / (r12 + r22) * u1y + (2 * r22) / (r12 + r22) * u2y;
        (*p).velocity.x = (r22 - r12) / (r12 + r22) * u2x + (2 * r22) / (r12 + r22) * u1x;
        (*p).velocity.y = (r22 - r12) / (r12 + r22) * u2y + (2 * r22) / (r12 + r22) * u1y;
    }
};

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle System");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    sf::Clock clock;
    sf::Clock clock2;
    sf::Clock clock3;
    sf::Clock clock4;
    sf::Clock clock5;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (clock.getElapsedTime().asSeconds() > 0.03f) {
            particles.push_back(Particle(sf::Vector2f(400, 300))); // Generate new particle
            clock.restart();
        }

        if (clock2.getElapsedTime().asSeconds() > 0.03f) {
            particles.push_back(Particle(sf::Vector2f(600, 200))); // Generate new particle
            clock2.restart();
        }

        if (clock3.getElapsedTime().asSeconds() > 0.03f) {
            particles.push_back(Particle(sf::Vector2f(200, 400))); // Generate new particle
            clock3.restart();
        }

        if (clock4.getElapsedTime().asSeconds() > 0.03f) {
            particles.push_back(Particle(sf::Vector2f(200, 200))); // Generate new particle
            clock4.restart();
        }

        if (clock5.getElapsedTime().asSeconds() > 0.03f) {
            particles.push_back(Particle(sf::Vector2f(400, 400))); // Generate new particle
            clock5.restart();
        }

        for (int i = 0; i < particles.size(); i++) {
            particles[i].update();
            if (particles[i].shape.getPosition().x < 0 || particles[i].shape.getPosition().x > window.getSize().x || particles[i].shape.getPosition().y < 0 || particles[i].shape.getPosition().y > window.getSize().y) {
                particles.erase(particles.begin() + i);
            }
        }
            
            

        for (int i = 0; i < particles.size(); i++) {
            for (int j = i + 1; j < particles.size(); j++) {
                if (particles[i].shape.getGlobalBounds().intersects(particles[j].shape.getGlobalBounds())) {
                    particles[i].collide(&particles[j]);
                }
            }
        }

        window.clear();
        for (const auto& particle : particles)
            window.draw(particle.shape);
        window.display();
    }

    return 0;
}
