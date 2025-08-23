#pragma once
#include <string>
using namespace std;

string logo_button_qss = R"(
	QPushButton{
		background-color:rgb(54,54,54);
		border:none;
		font-family:Microsoft YaHei;
		font-size:18px; 
		color:rgb(255,255,255);
	}

	QPushButton::menu-indicator:open{
		image:url(:/titlebar/resources/titleBar/down_arrow.svg);
		subcontrol-position:right center;
		subcontrol-origin:padding;border:none;
	}

	QPushButton::menu-indicator:closed{
		image:url(:/titlebar/resources/titleBar/up_arrow.svg);
		subcontrol-position:right center;
		subcontrol-origin:padding;border:none;
	})";

string menu_qss = R"(
	QMenu{background-color:rgb(253,253,253);}
	QMenu::item{
		font:16px;
		background-color:rgb(253,253,253);
		padding:8px 32px;
		margin:0px 8px;
		border-bottom:1px solid #DBDBDB;}
		QMenu::item:selected{background-color: #FFF8DC;})";

string minimode_qss = R"(
	QPushButton{
		background-image:url(:/titlebar/resources/titleBar/minimode.svg);
		border:none
	}

	QPushButton:hover{
		background-color:rgb(99, 99, 99);
		background-image:url(:/titlebar/resources/titleBar/minimode_hover.svg);
		border:none;
	}
)";

string settop_qss = R"(
	QPushButton{
		background-image:url(:/titlebar/resources/titleBar/settop.svg);
		border:none
	}

	QPushButton:hover{
		background-color:rgb(99, 99, 99);
		background-image:url(:/titlebar/resources/titleBar/settop_hover.svg);border:none;
	}
)";

string min_qss = R"(
	QPushButton{background-image:url(:/titlebar/resources/titleBar/min.svg);border:none}
		QPushButton:hover{
		background-color:rgb(99, 99, 99);
		background-image:url(:/titlebar/resources/titleBar/min_hover.svg);border:none;}
	)";

string max_qss = R"(
	QPushButton{background-image:url(:/titlebar/resources/titleBar/normal.svg);border:none}
				 QPushButton:hover{
				 background-color:rgb(99, 99, 99);
				 background-image:url(:/titlebar/resources/titleBar/normal_hover.svg);border:none;}
	)";

string close_qss = R"(
	QPushButton{background-image:url(:/titlebar/resources/titleBar/close.svg);border:none}
		QPushButton:hover{
		background-color:rgb(99, 99, 99);
		background-image:url(:/titlebar/resources/titleBar/close_hover.svg);border:none;}
	)";
