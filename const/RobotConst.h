#pragma once
#include <QString.h>
#include <QSize.h>

namespace ROBOT {

	const qreal SCALE_FACTOR_MIN = 0.3;
	const qreal SCALE_FACTOR_MAX = 3;


	const QPointF OBJ_DEF_ABS_POS = QPointF(-9999999999, -9999999999);

	const QString OBJ_DEF_NAME_COMPONENT = "ComponentView";
	const QString OBJ_DEF_NAME_ACTION = "ActionView";

	const QString STYLE_FONT = "fill: #fff;font - family: \"Helvetica Neue\", Helvetica, sans - serif;font - size: 12pt;font - weight: 500; ";
	
	const int OBJ_KEY_COMPONENT = 10000;
	const int OBJ_KEY_COMPONENT_TYPE = OBJ_KEY_COMPONENT + 1;
	const int OBJ_KEY_COMPONENT_NAME = OBJ_KEY_COMPONENT + 2;
	const int OBJ_KEY_COMPONENT_INNEST = OBJ_KEY_COMPONENT + 3;
	const int OBJ_KEY_COMPONENT_SLOT = OBJ_KEY_COMPONENT + 4;

	const QString FILE_NAME_TEST = ":/resource/test.svg";
	const QString FILE_NAME_INPUT = ":/resource/input.svg";

	const QString COLOR_PINK = "#BA4FBB";
	const QString COLOR_PINK_STROKE = "#DB5FD9";
	const QString COLOR_BLUE = "#0175d9";
	const QString COLOR_BLUE_STROKE = "#6297F4";
	const QString COLOR_PURPLE = "#9A67FF";
	const QString COLOR_PURPLE_STROKE = "#BC8BFF";
	const QString COLOR_ORANGE = "#FFAB19";
	const QString COLOR_ORANGE_STROKE = "#9B5F00";
	const QString COLOR_ROYAL_BLUE = "#5CB1D6";
	const QString COLOR_ROYAL_BLUE_STROKE = "#2E8EB8";

	const QString COLOR_WHITE = "#FFFFFF";

	const QString SVG_COM_BACKGROUND_NORM = "<svg><path stroke=\"%5\" stroke-width=\"3px\" fill=\"%3\" fill-opacity=\"%4\" d=\"m 0 4 A 4 4 0 0 1 4 0 H 12 c 2 0 3 1 4 2 l 4 4 c 1 1 2 2 4 2 h 12 c 2 0 3 -1 4 -2 l 4 -4 c 1 -1 2 -2 4 -2 H %1 a 4 4 0 0 1 4 4 v %2 a 4 4 0 0 1 -4 4 H 48 c -2 0 -3 1 -4 2 l -4 4 c -1 1 -2 2 -4 2 h -12 c -2 0 -3 -1 -4 -2 l -4 -4 c -1 -1 -2 -2 -4 -2 H 4 a 4 4 0 0 1 -4 -4 z\"></path></svg>";
	const QString SVG_COM_BACKGROUND_NEST = "<svg><path stroke=\"%5\" stroke-width=\"3px\" fill=\"%3\" fill-opacity=\"%4\" d=\"m 0 4 A 4 4 0 0 1 4 0 H 12 c 2 0 3 1 4 2 l 4 4 c 1 1 2 2 4 2 h 12 c 2 0 3 -1 4 -2 l 4 -4 c 1 -1 2 -2 4 -2 H %1 a 4 4 0 0 1 4 4 v 40 a 4 4 0 0 1 -4 4 H 64 c -2 0 -3 1 -4 2 l -4 4 c -1 1 -2 2 -4 2 h -12 c -2 0 -3 -1 -4 -2 l -4 -4 c -1 -1 -2 -2 -4 -2 h -8 a 4 4 0 0 0 -4 4 v %2 a 4 4 0 0 0 4 4 h 8 c 2 0 3 1 4 2 l 4 4 c 1 1 2 2 4 2 h 12 c 2 0 3 -1 4 -2 l 4 -4 c 1 -1 2 -2 4 -2 H %1 H %1 a 4 4 0 0 1 4 4 v 24 a 4 4 0 0 1 -4 4 H 48 c -2 0 -3 1 -4 2 l -4 4 c -1 1 -2 2 -4 2 h -12 c -2 0 -3 -1 -4 -2 l -4 -4 c -1 -1 -2 -2 -4 -2 H 4 a 4 4 0 0 1 -4 -4 z\"></path></svg>";
	const QString SVG_INPUT = "<svg><path stroke=\"%2\" stroke-width=\"3px\" fill=\"#FFFFFF\" fill-opacity=\"1\" d=\"m 0 0 m 16 0 H %1 a 16 16 0 0 1 0 32 H 16 a 16 16 0 0 1 0 -32 z\"></path></svg>";

	const unsigned int DEFALUT_MAX_ID = 4294967295;
}