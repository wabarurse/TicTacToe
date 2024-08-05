//
//  Alert.swift
//  TicTacToeUI2
//
//  Created by Richard Huang on 2024-08-05.
//

import SwiftUI

struct AlertItem: Identifiable {
    let id = UUID()
    var title: Text
    var message: Text
    var button: Text
}

struct AlertContent {
    static let humanWin = AlertItem(title: Text("You won!"), message: Text("Thats impossible, what happened?!"), button: Text("Fix code"))
    static let computerWin = AlertItem(title: Text("You lost"), message: Text("Lost to a comptuer, smh"), button: Text("Try again"))
    static let draw = AlertItem(title: Text("Draw"), message: Text("Expected"), button: Text("Rematch"))


}
