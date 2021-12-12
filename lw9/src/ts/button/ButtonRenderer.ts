import {Signal} from "../Signal";

class ButtonRenderer {
    private buttonHTML = document.createElement('button')
    private readonly m_text: string
    private onClickSignal = new Signal<void>()

    constructor(text: string, classList: Array<string>) {
        this.m_text = text
        classList.forEach(className => this.buttonHTML.classList.add(className))
    }

    getOnClickSignal() {
        return this.onClickSignal
    }

    render(parentElement: HTMLElement) {
        this.buttonHTML.innerHTML = this.m_text

        this.buttonHTML.onclick = () => this.onClickSignal.dispatch()

        parentElement.appendChild(this.buttonHTML)
    }
}

export {
    ButtonRenderer,
}