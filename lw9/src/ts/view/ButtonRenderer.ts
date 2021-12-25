import {Signal} from "../common/Signal";
import {Renderer} from "./Renderer";
import {TagName} from "../common/TagName";

class ButtonRenderer {
    private m_renderer: Renderer = new Renderer(TagName.BUTTON)
    private readonly m_text: string

    constructor(text: string, onClick: (e: Event) => void, classList: Array<string>) {
        this.m_text = text
        classList.forEach(className => this.m_renderer.addClassName(className))
        this.m_renderer.setInnerHTML(this.m_text)
        this.m_renderer.addEventListener('click', (e) => onClick(e))
    }

    render(parentElement: HTMLElement) {
        parentElement.appendChild(this.m_renderer.getDomElement())
    }
}

export {
    ButtonRenderer,
}