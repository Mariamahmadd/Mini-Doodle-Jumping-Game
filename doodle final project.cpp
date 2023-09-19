#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace sf;
using namespace std;

struct point
{
    int x, y;
};


int main() {
    srand(time(0));
    RenderWindow window(VideoMode(400, 533), "SFML");
    window.setFramerateLimit(60);
    
    Texture backgroundTex, doodleTex, platTex;

    backgroundTex.loadFromFile("materials/background.png");
    platTex.loadFromFile("materials/platform.png");
    doodleTex.loadFromFile("materials/doodle.png");
    
    Music music;
    music.openFromFile("materials/background.wav");

    SoundBuffer soundB;
    soundB.loadFromFile("materials/jump.wav");
    Sound sound;
    sound.setBuffer(soundB);
    float volume = 100;
    music.play();
    music.setVolume(100.0);


    Sprite background(backgroundTex), doodle(doodleTex), plat(platTex);
    point plates[10];
    for (int i = 0;i < 10;i++) {
        plates[i].x = rand() % 400;
        plates[i].y = rand() % 533;

    }


    doodle.setOrigin(doodle.getGlobalBounds().width / 2, doodle.getGlobalBounds().height / 2);
    doodle.setPosition(window.getSize().x / 2, 533 - doodle.getGlobalBounds().height / 2);

    bool isJump = false;

    float vSpeed = 0, hSpeed = 0;
    float gravity = 0.2;

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;


    while (window.isOpen()) {
        //Event Handling

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) { window.close(); }
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Left && doodle.getPosition().x > doodle.getGlobalBounds().width / 2) {
                    x -= 10;
                    doodle.setScale(1, 1);
                }
                if (e.key.code == Keyboard::Right && doodle.getPosition().x < window.getSize().x - doodle.getGlobalBounds().width / 2) {
                    x += 10;
                    doodle.setScale(-1, 1);
                }
                if (e.key.code == Keyboard::Space) {
                    isJump = true;
                    sound.play();
                }
                if (e.key.code == Keyboard::A) {
                    volume += 10;
                }
                if (e.key.code == Keyboard::B) {
                    volume -= 10;
                }
                if (e.key.code == Keyboard::P) {
                    music.pause();
                }
                if (e.key.code == Keyboard::O) {
                    music.play();
                }
            }
        }


        dy += 0.2;
        y += dy;
        if (y > 500) 
            dy = -10;
        if (y < h)
           
            for (int i = 0;i < 10;i++)
            {
                sound.play();
                y = h;
                plates[i].y = plates[i].y - dy;
                if (plates[i].y > 533) { plates[i].y = 0; plates[i].x = rand() % 400; }
            }

        for (int i = 0;i < 10;i++)
            if ((x + 50 > plates[i].x) && (x + 20 < plates[i].x + 68)
                && (y + 70 > plates[i].y) && (y + 70 < plates[i].y + 14) && (dy > 0))  dy = -10;


        doodle.setPosition(x, y);
        
        //logic
        if (doodle.getPosition().y >= 533 - doodle.getGlobalBounds().height / 2) vSpeed = 0;


        if (vSpeed != 0) vSpeed += 0.2;
        if (isJump) {
            vSpeed = -5;
            isJump = false;
        }

        doodle.move(hSpeed, vSpeed);
        window.clear();
        window.draw(background);
        for (int i = 0;i < 10;i++)
        {
            plat.setPosition(plates[i].x, plates[i].y);
            window.draw(plat);
        }


        window.draw(doodle);
        window.display();
        music.setVolume(volume);

    }


    return 0;
}
