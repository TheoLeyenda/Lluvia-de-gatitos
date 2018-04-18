#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
using namespace std;
int main()
{
	//TOMAR EN CUENTA ANTES DE LEER EL CODIGO:
	//- EL AUDIO DEL JUEGO SOLO FUNCIONA SI SE DEPLURA EL PROYECTO DESDE VISUAL STUDIO.
	//- ATRAPA A LOS GATITOS ;)
	random_device random;
	float velocidadGatuna = 0.1f;
	bool musicaPlay = false;
	int puntaje = 0;
	static int mayorPuntaje = 0;
	int Xpuntaje=50;
	int Ypuntaje=40;
	int pausa = 0;
	int vidas = 3;
	bool gameOver = false;
	bool jugar = false;
	bool entrar1 = false;
	bool entrar2 = false;
	bool entrar3 = false;
	int opcion = 0;
	sf::RenderWindow window(sf::VideoMode(640, 480), "LLuvia de Gatitos");
	
	//declaramos la textura.
	sf::Texture textureFondo;
	sf::Texture texturaJugador;
	sf::Texture texturaGatito;
	//declaro fuente de texto
	sf::Font fuenteTexto;
	sf::Font fuenteTexto1;
	sf::Font fuenteTexto2;
	sf::Text PuntajeTexto;
	sf::Text mejorPuntaje;
	sf::Text vidasTexto;
	sf::Text numeroVidas;
	sf::Text numeroMejorPuntaje;
	sf::Text numeroPuntaje;
	sf::Text gameOverTexto;

	//declaramos el buffer para el sonido/audio.
	sf::SoundBuffer bufferAgarrarGato;
	sf::SoundBuffer bufferGatoMuere;
	sf::Music fondoMusica;
	sf::Music musicaMenu;

	//menu-declaracion
	sf::Texture texturaMenu;
	sf::Texture texturaControles;
	sf::Texture texturaCreditos;
	//audio/sonido- buscar archivo
	bufferAgarrarGato.loadFromFile("../librerias del proyecto/efectos de sonido/opcion4-agarrarGato.wav");
	fondoMusica.openFromFile("../librerias del proyecto/efectos de sonido/opcion1_MusicaJuego.ogg");
	bufferGatoMuere.loadFromFile("../librerias del proyecto/efectos de sonido/gatoCaido1.wav");
	fondoMusica.setVolume(2.5);
	fondoMusica.setLoop(true);
	bufferAgarrarGato.loadFromSamples(NULL, NULL, 1, 2);
	bufferGatoMuere.loadFromSamples(NULL, NULL, 1, 2);
	sf::Sound sonidoGatoMuere;
	sf::Sound sonidoAgarrarGato;
	sonidoGatoMuere.setBuffer(bufferGatoMuere);
	sonidoAgarrarGato.setBuffer(bufferAgarrarGato);
	
	//menu-buscar archivo
	texturaMenu.loadFromFile("../librerias del proyecto/sprites/menu.png",sf::IntRect(0,0,640,480));
	texturaCreditos.loadFromFile("../librerias del proyecto/sprites/Creditos.png", sf::IntRect(0, 0, 640, 480));
	texturaControles.loadFromFile("../librerias del proyecto/sprites/Controles.png",sf::IntRect(0,0,640,480));
	//textos
	fuenteTexto.loadFromFile("../librerias del proyecto/Hanged Letters.ttf");
	fuenteTexto1.loadFromFile("../librerias del proyecto/Impact Label.ttf");
	fuenteTexto2.loadFromFile("../librerias del proyecto/Ribbons-and-banners.ttf");

	gameOverTexto.setFont(fuenteTexto1);
	gameOverTexto.setPosition(180, 200);
	gameOverTexto.setCharacterSize(50);

	PuntajeTexto.setFont(fuenteTexto);
	PuntajeTexto.setPosition(Xpuntaje-20, Xpuntaje);
	PuntajeTexto.setCharacterSize(30);
	
	numeroPuntaje.setFont(fuenteTexto);
	numeroPuntaje.setPosition(Xpuntaje + 80, Ypuntaje+12);
	numeroPuntaje.setCharacterSize(30);

	vidasTexto.setFont(fuenteTexto);
	vidasTexto.setPosition(Xpuntaje + 450, Ypuntaje+12);
	vidasTexto.setCharacterSize(30);

	numeroVidas.setFont(fuenteTexto);
	numeroVidas.setPosition(Xpuntaje + 530, Ypuntaje+12);
	numeroVidas.setCharacterSize(30);

	mejorPuntaje.setFont(fuenteTexto);
	mejorPuntaje.setPosition(Xpuntaje-20, Ypuntaje+50);
	mejorPuntaje.setCharacterSize(30);

	//Cargamos la textura.
	textureFondo.loadFromFile("../librerias del proyecto/sprites/Fondo_Nivel_1.png", sf::IntRect(0, 0, 640, 480));
	texturaJugador.loadFromFile("../librerias del proyecto/sprites/norita.png", sf::IntRect(0, 0, 40, 48));
	texturaGatito.loadFromFile("../librerias del proyecto/sprites/gatito.png", sf::IntRect(0, 0, 48, 32));
	
	//actualizamos los pixeles de la imagen
	sf::Image imageFondo;
	sf::Image imageJugador;
	sf::Image imageGatito;
	sf::Image imageMenu;
	sf::Image imageControles;
	sf::Image imageCreditos;
	texturaCreditos.update(imageCreditos);
	texturaMenu.update(imageMenu);
	texturaControles.update(imageControles);
	textureFondo.update(imageFondo);
	texturaJugador.update(imageJugador);
	texturaGatito.update(imageGatito);

	//suavisamos la imagen     
	//tip: 
	//hay varias formas y esta es una, para buscar mas formas de suavisar imagenes ver pagina principal de SFML-> tutorial -> sprite y texturas.
	texturaMenu.setSmooth(true);
	texturaControles.setSmooth(true);
	texturaCreditos.setSmooth(true);
	textureFondo.setSmooth(true);
	texturaJugador.setSmooth(true);
	texturaGatito.setSmooth(true);
	//creamos el sprite

	sf::Sprite spriteFondo;
	sf::Sprite spriteJugador;
	sf::Sprite spriteGatito;
	sf::Sprite spriteMenu;
	sf::Sprite spriteControles;
	sf::Sprite spriteCreditos;

	spriteCreditos.setTexture(texturaCreditos);
	spriteMenu.setTexture(texturaMenu);
	spriteControles.setTexture(texturaControles);
	spriteFondo.setTexture(textureFondo);
	spriteJugador.setTexture(texturaJugador);
	spriteJugador.setPosition(320,480-48);
	spriteGatito.setTexture(texturaGatito);
	spriteGatito.setPosition(rand()%600, 0);
	window.setFramerateLimit(500);
	sf::Event event;
	while (window.isOpen())
	{
		window.clear();
		//event.TouchBegan;
		//event.TouchMoved;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && !jugar)
		{
			opcion = 0;
		}
		//verifico si aprieta una tecla en este caso Escape/ESC
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		//-------------------------------------------------------------
		//Pasaje de Pantallas(basicamente escribo sobre la imagen anterior, leer codigo igual, CODIGO ENTERO, DESDE LINEA 0(? ).
		if (opcion == 0) {
			window.draw(spriteFondo);
			window.draw(spriteMenu);
			entrar1 = true;
			entrar2 = true;
			entrar3 = true;
			vidas = 3;
			velocidadGatuna = 0.1f;
			gameOver = false;
			fondoMusica.stop();
			mejorPuntaje.setPosition(Xpuntaje - 20, Ypuntaje + 50);
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || opcion == 1) && opcion == 0 && entrar1 )
		{
			//Juego(habilito el juego en cada loop)
			opcion = 1;
			window.clear();
			jugar = true;
			entrar2 = false;
			entrar3 = false;
			fondoMusica.play();
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || opcion == 2) && !jugar && entrar2 )
		{
			window.clear();
			opcion = 2;
			window.draw(spriteFondo);
			window.draw(spriteControles);
			entrar1 = false;
			entrar3 = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
			{
				//si preciono tab seteo la opcion en 0 para que valla al menu
				opcion = 0;
			}
		
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || opcion == 3) && !jugar && entrar3)
		{
			window.clear();
			opcion = 3;
			window.draw(spriteFondo);
			window.draw(spriteCreditos);
			entrar1 = false;
			entrar2 = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) 
			{
				//si preciono tab seteo la opcion en 0 para que valla al menu
				opcion = 0;
			}
		}
		//-----------------------------------------------------------------------------------------------------
		if (jugar) {
			window.clear();
			if (vidas <= 0) {
				gameOverTexto.setString("Game Over");
				mejorPuntaje.setPosition(210, 260);
				
				gameOver = true;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
				{
					jugar = false;
					opcion = 0;
					if (puntaje > mayorPuntaje) 
					{
						mayorPuntaje = puntaje;
					}
					puntaje = 0;
				}
				velocidadGatuna = 0;
			}
			if (spriteJugador.getPosition().x > 640 - 40) {
				spriteJugador.setPosition(0, spriteJugador.getPosition().y);
			}
			if (spriteJugador.getPosition().x < 0) {
				spriteJugador.setPosition(600, spriteJugador.getPosition().y);
			}
			vidasTexto.setString("Vidas:");
			numeroVidas.setString(to_string(vidas));
			PuntajeTexto.setString("Puntaje:");
			numeroPuntaje.setString(to_string(puntaje));
			mejorPuntaje.setString("Mejor Puntaje:" + to_string(mayorPuntaje));
			
			spriteGatito.setPosition(spriteGatito.getPosition().x, spriteGatito.getPosition().y + velocidadGatuna);
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			//coliciones:
			if (spriteJugador.getGlobalBounds().intersects(spriteGatito.getGlobalBounds()))
			{
				sonidoAgarrarGato.setVolume(1.5);
				sonidoAgarrarGato.play();
				spriteGatito.setPosition(rand() % 600, 0);
				puntaje = puntaje + 10;
				velocidadGatuna = velocidadGatuna + 0.02f;
				

			}
			//-----------------------------
			if (spriteGatito.getPosition().y >= (480 - 32) && !gameOver)
			{
				sonidoGatoMuere.setVolume(2.5);
				sonidoGatoMuere.play();
				spriteGatito.setPosition(rand() % 600, 0);
				vidas--;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !gameOver)
			{
				spriteJugador.setPosition(spriteJugador.getPosition().x + 0.5f, spriteJugador.getPosition().y);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !gameOver)
			{
				spriteJugador.setPosition(spriteJugador.getPosition().x - 0.5f, spriteJugador.getPosition().y);
			}
			window.clear();
			//dibujo el sprite
			window.draw(spriteFondo);
			window.draw(spriteJugador);
			window.draw(spriteGatito);
			window.draw(PuntajeTexto);
			window.draw(numeroPuntaje);
			window.draw(vidasTexto);
			if (mayorPuntaje > 0) 
			{
				window.draw(mejorPuntaje);
			}
			if (vidas <= 0) 
			{
				window.draw(gameOverTexto);
				if (puntaje > mayorPuntaje)
				{
					mayorPuntaje = puntaje;
				}
				window.draw(mejorPuntaje);

			}
			window.draw(numeroVidas);
		}
		window.display();
	}
	
	return 0;
}
