#include "textBox.h"
TextBox::TextBox( float x, float y, float width, float height, size_t maxLength, sf::Font &MyFont, bool selected){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->isSelected = selected;
    this->maxLength = maxLength;

    this->text.setString("");
    this->text.setFont(MyFont);
    this->text.setFillColor(Color::Black);
    this->text.setCharacterSize(30);
    this->text.setPosition(sf::Vector2f(x+padding, y+padding));
}

void TextBox::inputLogic(int charTyped){
    if(charTyped == ENTER_KEY){
        this->setIsSelected(false);
        return;
    }else if(charTyped==DELETE_KEY){
        if(input.str().length() > 0 ){
            deleteLastCharacter();
        }
    } else{
        input << static_cast<char>(charTyped);
    }
    text.setString(input.str()+ "_");      
}

void TextBox::typeCharacter(Event in){
    if(isSelected){
        int charTyped  = in.text.unicode;
        if(charTyped < 128){
            if(input.str().length()<maxLength){
                inputLogic(charTyped);
            }
            else if(input.str().length() >= maxLength && charTyped == DELETE_KEY){
                deleteLastCharacter();
            }
        }
    }
}

bool TextBox::isHovered(Vector2i mouse_position){
    float m_x = float(mouse_position.x);
    float m_y = float(mouse_position.y);

    return (m_x>=x && m_x<=x+width && m_y>=y && m_y<=y+height);
}

void TextBox::setIsSelected(bool flag){
    this->isSelected = flag;
    if(!flag){    
        text.setString(input.str());        
    }
    if(flag){
        text.setString("_");
        input.str("");
    }
}

void TextBox::deleteLastCharacter(){
    std::string strInput = input.str();
    strInput.erase(strInput.end()-1);
    input.str("");
    input<< strInput;
    text.setString(input.str());
}