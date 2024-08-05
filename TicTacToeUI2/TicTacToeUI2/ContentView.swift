//
//  ContentView.swift
//  TicTacToeUI2
//
//  Created by Richard Huang on 2024-08-01.
//

import SwiftUI

struct ContentView: View {
    
    @State private var moves: [Move?] = Array(repeating: nil, count: 9)
    @State private var board: [String] = Array(repeating: "_", count: 9)
    @State private var numVacant = 9
    
    let columns: [GridItem] = [GridItem(.flexible()),
                               GridItem(.flexible()),
                               GridItem(.flexible()) ]
    
    var body: some View {
        LazyVGrid(columns: columns, spacing: 20) {
            ForEach(0..<9) { i in
                ZStack {
                    Circle()
                        .foregroundColor(.black).opacity(0.8)
                    
                    Image(systemName: moves[i]?.icon ?? "")
                        .resizable()
                        .frame(width: 40, height: 40)
                        .foregroundColor(.white)
                    
                }
                .onTapGesture {

                    if(moves[i] == nil) {
                        moves[i] = Move(player: .human, index: i)
                        board[i] = "o"
                        numVacant -= 1
                    }
                    printBoard()

                    
                    if(determineWinner() == "o") {
                        print("Human win")
                    }
                    
//                    computerMove()
//                    printBoard()
                    
                    
                    
                    DispatchQueue.main.asyncAfter(deadline: .now() + 0.5) {
                        let computerPosition = computerMove()
                        print(computerPosition)
                        moves[computerPosition] = Move(player: .computer, index: computerPosition)
                        board[computerPosition] = "x"
                        numVacant -= 1
                        printBoard()
                        
                        if(determineWinner() == "x") {
                            print("Computer win")
                        }
                        


                    }
                    
                    
                    
                    
                    
                }
            }
        }
        .padding(20)
    }
    
    func printBoard() {
        for i in 0..<9 {
            print(board[i], terminator: "");
            
            if((i + 1) % 3 == 0) {
                print("\n");
            }
            
        }
    }
    
    
    func determineWinner() -> String {
        var winner: String = "/"
        
        // horizontal
        for i in stride(from: 0, through: 6, by: 3) {
            if(board[i] == board[i + 1] && board[i] == board[i + 2] && board[i] != "_") {
                winner = board[i]
            }
        }
        
        // vertical
        for i in stride(from: 0, through: 2, by: 1) {
            if(board[i] == board[i + 3] && board[i] == board[i + 6] && board[i] != "_") {
                winner = board[i]
            }
        }
        
        //diagonal
        if(board[0] == board[4] && board[0] == board[8] && board[0] != "_") {
            winner = board[0]
        } else if(board[2] == board[4] && board[2] == board[6] && board[2] != "_") {
            winner = board[2]
        }
        
        
        //tie
        if(winner == "/" && numVacant == 0) {
            winner = "t"
        }
        
        
        return winner;
        
        
    }
    
    func minmax(isMaximizing: Bool) -> Int {
        let winner: String = determineWinner()
        
        if(winner != "/") {
            if(winner == "x") {
                return 10 + numVacant
            } else if(winner == "o") {
                return -10 - numVacant
            } else {
                return 0;
            }
        }
        
        if(isMaximizing) {
            var bestScore: Int = -100
            for i in 0..<9 {
                if (board[i] == "_") {
                    
                    board[i] = "x"; numVacant-=1
                    
                    let currScore: Int = minmax(isMaximizing: false)
                    
                    board[i] = "_"; numVacant+=1
                    
                    bestScore = max(currScore, bestScore)
                }
            }
            
            return bestScore;
            
        } else {
            var bestScore: Int = 100
            for i in 0..<9 {
                if (board[i] == "_") {
                     
                    board[i] = "o"; numVacant-=1
                    
                    let currScore: Int = minmax(isMaximizing: true)
                    
                    board[i] = "_"; numVacant+=1
                    
                    bestScore = min(currScore, bestScore)
                }
            }
            
            return bestScore;
            
        }
        
    }
    
    
    func computerMove() -> Int{
        var bestScore: Int = -100
        var coord: Int = -1
        
        for i in 0..<9 {
            if (board[i] == "_") {
                
                board[i] = "x"; numVacant-=1
                
                let currScore: Int = minmax(isMaximizing: false)
                
                board[i] = "_"; numVacant+=1

                if (currScore > bestScore) {
                    bestScore = currScore
                    coord = i
            
                }
            }
        }
        
        return coord
                
    }
    
}

func isSquareOccupied(in moves: [Move?], forIndex i: Int) -> Bool {
    return moves.contains(where: {$0?.index == i})
}

func randComputerMove(in moves: [Move?]) -> Int {
    var movePosition = Int.random(in: 0..<9)
    
    while isSquareOccupied(in: moves, forIndex: movePosition) {
        movePosition = Int.random(in: 0..<9)
    }
    
    return movePosition
    
}
    

enum Player {
    case human, computer
}

struct Move {
    let player: Player
    let index: Int
    
//    var char: Character {
//        return player == .human ? "o" : "x"
//    }
    
    var icon: String {
        return player == .human ? "circle" : "xmark"
    }
    
}

#Preview {
    ContentView()
}
