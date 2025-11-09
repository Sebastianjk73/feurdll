/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>

/**
 * Brings cocos2d and all Geode namespaces to the current scope.
 */
using namespace geode::prelude;

/**
 * `$modify` lets you extend and modify GD's classes.
 * To hook a function in Geode, simply $modify the class
 * and write a new function definition with the signature of
 * the function you want to hook.
 *
 * Here we use the overloaded `$modify` macro to set our own class name,
 * so that we can use it for button callbacks.
 *
 * Notice the header being included, you *must* include the header for
 * the class you are modifying, or you will get a compile error.
 *
 * Another way you could do this is like this:
 *
 * struct MyMenuLayer : Modify<MyMenuLayer, MenuLayer> {};
 */
#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	/**
	 * Typically classes in GD are initialized using the `init` function, (though not always!),
	 * so here we use it to add our own button to the bottom menu.
	 *
	 * Note that for all hooks, your signature has to *match exactly*,
	 * `void init()` would not place a hook!
	*/
	bool init() {
		/**
		 * We call the original init function so that the
		 * original class is properly initialized.
		 */
		if (!MenuLayer::init()) {
			return false;
		}

		/**
		 * You can use methods from the `geode::log` namespace to log messages to the console,
		 * being useful for debugging and such. See this page for more info about logging:
		 * https://docs.geode-sdk.org/tutorials/logging
		*/
		log::debug("Hello from my MenuLayer::init hook! This layer has {} children.", this->getChildrenCount());

		/**
		 * See this page for more info about buttons
		 * https://docs.geode-sdk.org/tutorials/buttons
		*/
		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
			this,
			/**
			 * Here we use the name we set earlier for our modify class.
			*/
			menu_selector(MyMenuLayer::onMyButton)
		);

		/**
		 * Here we access the `bottom-menu` node by its ID, and add our button to it.
		 * Node IDs are a Geode feature, see this page for more info about it:
		 * https://docs.geode-sdk.org/tutorials/nodetree
		*/
		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		/**
		 * The `_spr` string literal operator just prefixes the string with
		 * your mod id followed by a slash. This is good practice for setting your own node ids.
		*/
		myButton->setID("my-button"_spr);

		/**
		 * We update the layout of the menu to ensure that our button is properly placed.
		 * This is yet another Geode feature, see this page for more info about it:
		 * https://docs.geode-sdk.org/tutorials/layouts
		*/
		menu->updateLayout();

		/**
		 * We return `true` to indicate that the class was properly initialized.
		 */
		return true;
	}

	/**
	 * This is the callback function for the button we created earlier.
	 * The signature for button callbacks must always be the same,
	 * return type `void` and taking a `CCObject*`.
	*/
	void onMyButton(CCObject*) {
		FLAlertLayer::create("Eres muy fea", "Zuly fra", "Fea")->show();
	}
};

#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp> 

using namespace geode::prelude;

// --- 1. FUNCIÓN DE RESPUESTA DEL BOTÓN ---
// Esta función se ejecuta cuando el usuario toca el botón.
void onHelloButton(CCObject* sender) {
    // Muestra un mensaje pop-up en el juego (es una función de Geode/Cocos2d)
    FLAlertLayer::create("Mi Mod Personal", "¡Hola desde mi mod hecho en Android!", "OK")->show();
}


// --- 2. EL GANCHO ($modify) ---
// Hookeamos el MenuLayer para añadir nuestro botón.
class $modify(MyMenuLayer, MenuLayer) {
    
    // Hookeamos la función 'init' que se ejecuta al cargar el menú.
    bool init() {
        // Llama a la función 'init' original. ¡ES OBLIGATORIO!
        if (!MenuLayer::init()) {
            return false;
        }

        // --- CÓDIGO PARA AÑADIR EL BOTÓN ---
        
        // 3. Crear el objeto visual (texto "HOLA")
        auto buttonSprite = CCLabelTTF::create("HOLA", "Arial", 20.0f); 

        // 4. Crear el botón interactivo (CCMenuItemSpriteExtra)
        auto myButton = CCMenuItemSpriteExtra::create(
            buttonSprite, // Usamos el texto como la imagen del botón
            this,         // El objeto que tiene la función (esta clase)
            menu_selector(onHelloButton) // La función que llamará
        );

        // 5. Obtener la capa del menú existente para añadir nuestro botón
        auto menu = this->getChildByID("main-menu-node"); 

        // 6. Añadir el botón al menú
        menu->addChild(myButton);
        
        // 7. Colocar el botón en una posición visible (ej. en la esquina inferior izquierda)
        myButton->setPosition({-100.0f, -100.0f}); 

        // ---------------------------------

        log::info("Botón 'HOLA' añadido al menú principal.");
        
        return true;
    }
};
