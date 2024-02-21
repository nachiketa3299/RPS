#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Table;

namespace DIRECTION {
    const int EAST  = 1;
    const int WEST  = 2;
    const int NORTH = 3;
    const int SOUTH = 4;
}

class Dice {
private:
    struct Face {
        int east;
        int west;
        int top;
        int bottom;
        int north;
        int south;
    } faces { 0, 0, 0, 0, 0, 0 };
public:

    void rotate (int command) {
        int temp_bottom = this->faces.bottom;
        switch (command) {
            case DIRECTION::EAST:
                this->faces.bottom = this->faces.east;
                this->faces.east = this->faces.top;
                this->faces.top = this->faces.west;
                this->faces.west = temp_bottom;
                break;
            case DIRECTION::WEST:
                this->faces.bottom = this->faces.west;
                this->faces.west = this->faces.top;
                this->faces.top = this->faces.east;
                this->faces.east = temp_bottom;
                break;
            case DIRECTION::NORTH:
                this->faces.bottom = this->faces.north;
                this->faces.north = this->faces.top;
                this->faces.top = this->faces.south;
                this->faces.south = temp_bottom;
                break;
            case DIRECTION::SOUTH:
                this->faces.bottom = this->faces.south;
                this->faces.south = this->faces.top;
                this->faces.top = this->faces.north;
                this->faces.north = temp_bottom;
                break;
        }
        return;
    }

    int getBottom (void) const {
        return this->faces.bottom;
    }

    void setBottom (int new_bottom)  {
        this->faces.bottom = new_bottom;
        return;
    }
    int getTop (void) const {
        return this->faces.top;
    }
};

class Map {
private:
    Table table;
public:
    Map (const Table& t) {
        this->table = t;
        return;
    }
    int getN (void) const {
        return this->table.size();
    }
    int getM (void) const {
        return this->table.front().size();
    }

    void print (void) const {
        std::cout << "Saved Map" << std::endl;
        for (const auto& l: this->table) {
            for (const auto& e: l) {
                std::cout << e << " ";
            }
            std::cout << std::endl;
        }
    }
    int getNumber (int x, int y) const {
        return this->table[x][y];
    }
    void setNumber (int x, int y, int new_number) {
        this->table[x][y] = new_number;
        return;
    }

};

class Handler {
private:
    Map *m;
    Dice *d;
    std::vector<int> commands;
    struct DicePos {
        int x;
        int y;
        DicePos (int x, int y) : x(x), y(y) {}
    } dicepos;
public:
    Handler (const Map& m, int x, int y, const std::vector<int>& commands) 
    : dicepos(x, y) {
        this->m = new Map(m);
        this->d = new Dice;
        this->commands = commands;
        return;
    }

    ~Handler (void) {
        delete m;
        delete d;
        return;
    }

private:
    void setDicePos (const DicePos& new_dicepos, int command) {
        this->dicepos = new_dicepos;
        this->d->rotate(command);
        return;
    }
    bool boundaryCheck (const DicePos& new_dicepos) const {
        bool c1 = new_dicepos.x >= 0 && new_dicepos.x <= this->m->getN() - 1;
        bool c2 = new_dicepos.y >= 0 && new_dicepos.y <= this->m->getM() - 1;
        return c1 && c2;
    }

    DicePos commandDicePos (int command) {
        switch (command) {
            case DIRECTION::EAST:
                return DicePos { this->dicepos.x, this->dicepos.y + 1 };
            case DIRECTION::WEST:
                return DicePos { this->dicepos.x, this->dicepos.y - 1 };
            case DIRECTION::NORTH:
                return DicePos { this->dicepos.x - 1, this->dicepos.y };
            case DIRECTION::SOUTH:
                return DicePos { this->dicepos.x + 1, this->dicepos.y };
            default:
                std::cerr << "Error" << std::endl;
                return DicePos { 0, 0 };
        }
    }

public:
    void process (void) {
        for (int i = 0; i < this->commands.size(); i++) {
            DicePos new_dicepos = this->commandDicePos(this->commands[i]);
            if (this->boundaryCheck(new_dicepos)) {
                this->setDicePos(new_dicepos, this->commands[i]);
                const int& x = this->dicepos.x;
                const int& y = this->dicepos.y;
                if (this->m->getNumber(x, y) == 0) {
                    this->m->setNumber(x, y, this->d->getBottom());
                } else {
                    this->d->setBottom(this->m->getNumber(x, y));
                    this->m->setNumber(x, y, 0);
                }
                std::cout << this->d->getTop() << std::endl;
            } else {
                ;
            }
        }
    }

};

int main (void) {
    int N, M, x, y, K;
    std::cin >> N >> M >> x >> y >> K;
    Table t (N, std::vector<int> (M));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cin >> t[i][j];
        }
    }

    std::vector<int> commands (K);

    for (int i = 0; i < K; i++) {
        std::cin >> commands[i];
    }

    Map m(t);
    Handler h(m, x, y, commands);
    h.process();
    
    return 0;
}
