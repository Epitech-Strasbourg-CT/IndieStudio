#include <stdio.h>
#include "../../include/irrKlang.h"

#if defined(WIN32)
#include <conio.h>
#else
#include "../common/conio.h"
#endif

#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")

struct SAppContext
{
	IrrlichtDevice *device;
	s32				counter;
	IGUIListBox*	listbox;
};

enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_NEW_WINDOW_BUTTON,
	GUI_ID_FILE_OPEN_BUTTON,
	GUI_ID_TRANSPARENCY_SCROLL_BAR
};

void setSkinTransparency(s32 alpha, irr::gui::IGUISkin * skin)
{
	for (s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
	{
		video::SColor col = skin->getColor((EGUI_DEFAULT_COLOR)i);
		col.setAlpha(alpha);
		skin->setColor((EGUI_DEFAULT_COLOR)i, col);
	}
}

class MyEventReceiver : public IEventReceiver
{
	public:
	MyEventReceiver(SAppContext & context) : Context(context) { }

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{

			case EGET_SCROLL_BAR_CHANGED:
				if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
				{
					s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					setSkinTransparency(pos, env->getSkin());
				}
				break;

			case EGET_BUTTON_CLICKED:
				switch(id)
				{
				case GUI_ID_QUIT_BUTTON:
					Context.device->closeDevice();
					return true;

				case GUI_ID_NEW_WINDOW_BUTTON:
					Context.listbox->addItem(L"File open");
					env->addFileOpenDialog(L"Please choose a file.", true, 0, -1, true);
					return true;

				case GUI_ID_FILE_OPEN_BUTTON:
				{
					Context.listbox->addItem(L"Window created");
					Context.counter += 30;
					if (Context.counter > 200)
						Context.counter = 0;

					IGUIWindow* window = env->addWindow(
						rect<s32>(100 + Context.counter, 100 + Context.counter, 300 + Context.counter, 200 + Context.counter),
						false, // modal?
						L"Test window");

					env->addButton(rect<s32>(100,240,110,240 + 32), 0, GUI_ID_FILE_OPEN_BUTTON,
						L"Play", L"Launch Game");
				}
					return true;
				default:
					return false;
				}
				break;

			case EGET_FILE_SELECTED:
			{
				IGUIFileOpenDialog* dialog =
					(IGUIFileOpenDialog*)event.GUIEvent.Caller;
				Context.listbox->addItem(dialog->getFileName());
			}
				break;

			default:
				break;
			}
		}

		return false;
	}
	private:
	SAppContext & Context;
};


int main(int argc, const char** argv)
{
	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	if (!engine)
	{
		printf("Could not startup engine\n");
		return 0; // error starting up the engine
	}
	engine->play2D("../../media/getout.ogg", true);
	printf("\nHello World!\n");
	do
	{
		printf("Press any key to play some sound, press 'q' to quit.\n");
		engine->play2D("../../media/bell.wav");
	}
	while(getch() != 'q')
	{
		video::E_DRIVER_TYPE driverType = driverChoiceConsole();
		if (driverType == video::EDT_COUNT)
			return
		IrrlichtDevice *device = createDevice(driverType,
			core::dimension2d<u32>(1920, 1080));
		if (device == 0)
			device->setWindowCaption(
				L"Irrlicht Engine - User Interface Demo");
		device->setResizable(true);
		video::IVideoDriver *driver = device->getVideoDriver();
		IGUIEnvironment *env = device->getGUIEnvironment();
		IGUISkin *skin = env->getSkin();
		IGUIFont *font = env->getFont(
			"../../media/fonthaettenschweiler.bmp");
		if (font)
			skin->setFont(font);
		skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
		env->addButton(rect<s32>(700, 340, 1220, 340 + 32), 0,
			GUI_ID_FILE_OPEN_BUTTON, L"Play", L"Launch Game");
		env->addButton(rect<s32>(700, 380, 1220, 380 + 32), 0,
			GUI_ID_NEW_WINDOW_BUTTON, L"Settings", L"Settings");
		env->addButton(rect<s32>(700, 420, 1220, 420 + 32), 0,
			GUI_ID_QUIT_BUTTON, L"Exit", L"Exit game");
		env->addStaticText(L"Volume Control:",
			rect<s32>(150, 20, 350, 40), true);
		IGUIScrollBar *scrollbar = env->addScrollBar(true,
			rect<s32>(150, 45, 350, 60), 0,
			GUI_ID_TRANSPARENCY_SCROLL_BAR);
		scrollbar->setMax(255);
		scrollbar->setPos(255);
		setSkinTransparency(scrollbar->getPos(), env->getSkin());
		scrollbar->setPos(
			env->getSkin()->getColor(EGDC_WINDOW).getAlpha());
		IGUIListBox *listbox = env->addListBox(
			rect<s32>(50, 140, 250, 210));
		SAppContext context;
		context.device = device;
		context.counter = 0;
		context.listbox = listbox;
		MyEventReceiver receiver(context);
		device->setEventReceiver(&receiver);
		env->addImage(
			driver->getTexture("../../media/Bomberman-icon.png"),
			position2d<int>(820, 10));
		while (device->run() && driver)
			if (device->isWindowActive()) {
				driver->beginScene(true, true,
					SColor(0, 200, 200, 200));
				env->drawAll();
				driver->endScene();
			}
		device->drop();
	}
	engine->drop();
	return 0;
}
