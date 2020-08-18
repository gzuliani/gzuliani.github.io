#!/usr/bin/python3
# -*- coding: utf-8 -*-


class Cell:

    def __init__(self):
        self.value = None
        self.candidates = [*range(1, 10)]

    def set(self, n):
        self.value = n
        self.candidates = []

    def remove_candidate(self, n):
        if n in self.candidates:
            self.candidates.remove(n)


class Board:

    def __init__(self):
        self.cells = [[Cell() for col in range(9)] for row in range(9)]
        self.rows = self.cells
        self.cols = [[self.cells[row][col] for row in range(9)]
                     for col in range(9)]
        self.sqrs = [[self.cells[square_top + row][square_left + col]
                     for row in range(3) for col in range(3)]
                     for square_top in [0, 3, 6] for square_left in
                     [0, 3, 6]]

    def __getitem__(self, key):
        return self.rows[key]

    def set(self, row, col, n):
        cell = self.cells[row][col]
        if cell.value:
            print('invalid move')
            return
        cell.set(n)
        self._remove_candidate_from_row(row, n)
        self._remove_candidate_from_col(col, n)
        square = 3 * int(row / 3) + int(col / 3)
        self._remove_candidate_from_square(square, n)

    def _remove_candidate_from_row(self, row, n):
        for cell in self.rows[row]:
            cell.remove_candidate(n)

    def _remove_candidate_from_col(self, col, n):
        for cell in self.cols[col]:
            cell.remove_candidate(n)

    def _remove_candidate_from_square(self, square, n):
        for cell in self.sqrs[square]:
            cell.remove_candidate(n)


class Terminal:

    def print_cell(self, cell):
        if cell.value:
            return ' {} '.format(str(cell.value))
        elif len(cell.candidates) == 1:
            return '<{}>'.format(cell.candidates[0])
        else:
            return '   '

    def print_board(self, board):
        print('╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗')
        for r, row in enumerate(board.rows):
            print('║', end='')
            for c, cell in enumerate(row):
                print('{}{}'.format(
                    self.print_cell(cell), '║' if c % 3 == 2 else '│'), end='')
            if r == 8:
                print('\n╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝')
            elif r % 3 == 2:
                print('\n╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣')
            else:
                print('\n╟───┼───┼───╫───┼───┼───╫───┼───┼───╢')

    def read_move(self, prompt):
        return input(prompt)


board = Board()

board.set(0, 0, 1)
board.set(0, 2, 7)
board.set(0, 4, 9)
board.set(0, 6, 6)
board.set(0, 7, 5)
board.set(0, 8, 8)

board.set(1, 2, 3)
board.set(1, 4, 6)
board.set(1, 5, 7)
board.set(1, 8, 4)

board.set(2, 3, 4)
board.set(2, 4, 1)
board.set(2, 6, 9)
board.set(2, 7, 7)

board.set(3, 3, 9)
board.set(3, 4, 3)

board.set(4, 0, 9)
board.set(4, 6, 3)
board.set(4, 7, 8)
board.set(4, 8, 6)

board.set(5, 2, 2)
board.set(5, 3, 7)
board.set(5, 6, 4)
board.set(5, 8, 1)

board.set(6, 0, 3)
board.set(6, 3, 6)
board.set(6, 5, 1)

board.set(7, 1, 5)
board.set(7, 6, 1)
board.set(7, 8, 9)

board.set(8, 0, 4)
board.set(8, 2, 1)
board.set(8, 3, 3)
board.set(8, 6, 7)
board.set(8, 8, 2)

terminal = Terminal()

while True:
    terminal.print_board(board)
    move = terminal.read_move('Your move (RCN): ')
    board.set(int(move[0]) - 1, int(move[1]) - 1, int(move[2]))
