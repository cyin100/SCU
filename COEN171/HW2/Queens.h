/*
 * Conner Yin
 *
 * Solve the n-Pieces problem of trying to place n identical pieces on
 * an n x n chessboard.
 *
 *      Knights         Bishops         Rooks           Queens          Amazons
 * 2    6               4               2               0               0
 * 3    36              26              6               0               0
 * 4    412             260             24              2               0
 * 5    9386            3368            120             10              0
 * 6    257318          53744           720             4               0
 * 7    8891854         1022320         5040            40              0
 * 8    379978716       22522960        40320           92              0
 * 9    19206532478     565532992       362880          352             0
 * 10   1120204619108   15915225216     3628800         724             4
 */

# ifndef QUEENS_H
# define QUEENS_H
# include <cstdlib>

// An abstract chess piece that cannot be instantiated.
// Methods for getting row, column, placing piece, virtual menaces
class Piece {
    protected:
        int _row, _column;

    public:
        Piece(){
            _row = 0;
            _column = 0;
        }
        int row() const{
            return _row;
        }
        int column() const {
            return _column;
        }
        void place(int row, int column){
            this->_row = row;
            this->_column = column;
        }
        virtual bool menaces(const Piece *piece){
            return false;
        }
};

// Rook class, menaces piece if row or column is same
class Rook : public virtual Piece {
    public:
        virtual bool menaces(const Piece *piece){
            return (this->row() == piece->row() || 
                    this->column() == piece->column());
        }
};

// Bishop class, menaces piece if slope is 1 or -1
class Bishop : public virtual Piece {
    public:
        virtual bool menaces(const Piece *piece){
            if(this->row() == piece->row()) return false;
            double slope = (double)(this->column() - piece->column()) / (double)(this->row() - piece->row());
            return slope == 1.0 || slope == -1.0;
        }
};

// Knight class, menaces piece if abs value of row difference is 2 and abs value of 
// column difference is 1 or vice versa
class Knight : public virtual Piece {
    public:
        virtual bool menaces(const Piece *piece){
            return (this->row()-piece->row() == 2 || this->row()-piece->row() == -2) && 
            (this->column()-piece->column() == 1 || this->column()-piece->column() == -1) ||
            (this->row()-piece->row() == 1 || this->row()-piece->row() == -1) && 
            (this->column()-piece->column() == 2 || this->column()-piece->column() == -2);
        }
};

// Queen class, menaces piece if rook or bishop can menace
class Queen : public Rook, public Bishop {
    public:
        virtual bool menaces(const Piece *piece){
            return Rook::menaces(piece) || Bishop::menaces(piece);
        }
};

// Amazon class, menaces piece if queen or knight can menace
class Amazon : public Queen, public Knight {
    public:
        virtual bool menaces(const Piece *piece){
            return Queen::menaces(piece) || Knight::menaces(piece);
        }
};

# endif /* QUEENS_H */
