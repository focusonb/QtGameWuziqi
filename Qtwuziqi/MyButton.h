#pragma once
#include <QPushButton>
class MyButton :
	public QPushButton
{
public:
	MyButton(QWidget *parent = 0)
	{
		setText("I am a button");
	}
private:
    void enterEvent(QEvent* e)
	{
		setStyleSheet("QPushButton{background: yellow;}");
		
	}
	void leaveEvent(QEvent* e)
	{
		setStyleSheet("QPushButton{background: white;}");
	}
};

