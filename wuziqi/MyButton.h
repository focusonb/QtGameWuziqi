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
	void enterEvent(QEvent* e) override
	{
		setStyleSheet("QPushButton{background: yellow;}");
		
	}
	void MyButton::leaveEvent(QEvent* e)
	{
		setStyleSheet("QPushButton{background: white;}");
	}
};

