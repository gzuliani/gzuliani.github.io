#!/usr/bin/python3
# -*- coding: utf-8 -*-

import collections
import random


class Cell:

    def __init__(self, row, col):
        self.row = row
        self.col = col
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
        self.cells = [[Cell(row, col) for col in range(9)] for row in range(9)]
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

    def cell_clusters(self):
        return self.rows + self.cols + self.sqrs

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


class Hint:

    def __init__(self, cell, value):
        self.cell = cell
        self.value = value


def find_lone_candidates(cells):
    histogram = collections.defaultdict(set)
    for cell in cells:
        for candidate in cell.candidates:
            histogram[candidate].add(cell)
    return [Hint(v.pop(), k) for k, v in histogram.items() if len(v) == 1]


def find_single_candidates(cells):
    return [Hint(cell, cell.candidates[0]) for cell in cells
            if len(cell.candidates) == 1]


def find_hints(board):
    return set([hint for row in board.rows for hint in
               find_single_candidates(row)] + [hint for cluster in
               board.cell_clusters() for hint in
               find_lone_candidates(cluster)])


def show_hint(board):
    hints = find_hints(board)
    if not hints:
        print('Sorry, no help available.')
        return
    hint = random.sample(hints, 1)[0]
    print('{}{}{}'.format(hint.cell.row + 1, hint.cell.col + 1, hint.value))

board = Board()

board.set(0, 1, 4)
board.set(0, 7, 2)

board.set(1, 0, 9)
board.set(1, 8, 3)

board.set(2, 2, 5)
board.set(2, 3, 7)
board.set(2, 5, 2)
board.set(2, 6, 6)

board.set(3, 2, 8)
board.set(3, 3, 6)
board.set(3, 5, 9)
board.set(3, 6, 4)

board.set(5, 2, 2)
board.set(5, 3, 3)
board.set(5, 5, 7)
board.set(5, 6, 5)

board.set(6, 2, 6)
board.set(6, 3, 5)
board.set(6, 5, 8)
board.set(6, 6, 1)

board.set(7, 0, 1)
board.set(7, 8, 9)

board.set(8, 1, 7)
board.set(8, 7, 4)

terminal = Terminal()
terminal.print_board(board)

while True:
    move = terminal.read_move('Your move (RCN or `H` for help): ')
    if move == 'H':
        show_hint(board)
    else:
        board.set(int(move[0]) - 1, int(move[1]) - 1, int(move[2]))
        terminal.print_board(board)
