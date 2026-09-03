import SwiftUI

struct ContentView: View {
    @StateObject private var model = ProofModel()

    var body: some View {
        ZStack(alignment: .bottom) {
            ARYarmiView(model: model, resetCounter: model.resetCounter)
                .ignoresSafeArea()

            VStack(spacing: 10) {
                Text(model.instruction)
                    .font(.callout)
                    .multilineTextAlignment(.center)
                    .padding(.horizontal, 14)
                    .padding(.vertical, 10)
                    .background(.ultraThinMaterial, in: RoundedRectangle(cornerRadius: 12))

                Button("Reset") {
                    model.reset()
                }
                .buttonStyle(.borderedProminent)
            }
            .padding()
        }
    }
}
