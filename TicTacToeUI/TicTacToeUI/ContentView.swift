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
    @State private var alertItem: AlertItem?
    @State private var boardDisabled = false
    
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

                    
                    if(determineWinner() == "o") {
                        alertItem = AlertContent.humanWin
                        return
                    } else if(determineWinner() == "t") {
                        alertItem = AlertContent.draw
                        return
                    }
                    
                    boardDisabled = true
                    
 
                    DispatchQueue.main.asyncAfter(deadline: .now() + 0.5) {
                        let computerPosition = computerMove()
                        moves[computerPosition] = Move(player: .computer, index: computerPosition)
                        board[computerPosition] = "x"
                        numVacant -= 1
                        
                        boardDisabled = false
                        
                        if(determineWinner() == "x") {
                            alertItem = AlertContent.computerWin
                            return
                        } else if(determineWinner() == "t") {
                            alertItem = AlertContent.draw
                            return
                        }
                    }
                }
            }
        }
        .padding(20)
        .disabled(boardDisabled)
        .alert(item: $alertItem, content: {alertItem in
            Alert(title: alertItem.title, message: alertItem.message, dismissButton: .default(alertItem.button, action: { resetGame() }))
        })
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
    
    func resetGame() {
        moves = Array(repeating: nil, count: 9)
        board = Array(repeating: "_", count: 9)
        numVacant = 9
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
