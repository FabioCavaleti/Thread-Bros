#ifndef _H_PLAYER
#define _H_PLAYER


class Player
{
    private:
        std::pair<int, int> pos, endPos;
        char table[8][30];

    public:
        Player(std::pair<int, int> pos, std::pair<int, int> endPos, char table[][30]);

        void Player::setPos(std::pair<int, int> pos);
        std::pair<int, int> Player::getPos();

        void Player::setEndPos(std::pair<int, int> endPos);
        std::pair<int, int> Player::getEndPos();

        int getX();
        int getY();

        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
};

#endif