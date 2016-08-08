
#include "rendimidi.h"
#include <Ogre.h>
#include <vector>
#include <iostream>

bool rendimidi_start()
{
	try
	{
		Ogre::String config = "";
		Ogre::String plugins = "";
		Ogre::String log = "rendimidi.log";

		auto root = new Ogre::Root(config, plugins, log);

		{
			std::vector<Ogre::String> plugins;
			plugins.push_back("RenderSystem_GL3Plus");
			// plugins.push_back("RenderSystem_Direct3D11");
			plugins.push_back("Plugin_ParticleFX");
			for (auto i : plugins)
				root->loadPlugin(OGRE_DEBUG_MODE ? i.append("_d") : i);
		}

		{
			const Ogre::RenderSystemList& render_system_list = root->getAvailableRenderers();
			if (render_system_list.size() == 0)
			{
				Ogre::LogManager::getSingleton().logMessage("Sorry, no rendersystem was found.");
				return false;
			}

			root->setRenderSystem(render_system_list[0]);
		}

		root->initialise(false, "", "");
		
		Ogre::RenderWindow* window = NULL;
		{
			Ogre::NameValuePairList params;
			params["FSAA"] = "0";
			params["vsync"] = "true";
			window = root->createRenderWindow("", 1366, 768, false, &params);
		}

		while (!window->isClosed())
		{
			Ogre::WindowEventUtilities::messagePump();
		}

		Ogre::LogManager::getSingleton().logMessage("Rendimidi finished.");
	}
	catch (Ogre::Exception &e)
	{
		std::cout << "Ogre::Exception: " << e.what() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "std::exception: " << e.what() << std::endl;
	}

	return 0;
}
