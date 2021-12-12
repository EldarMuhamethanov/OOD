import {Signal} from "../Signal";

const CANVAS_WIDTH = 640
const CANVAS_HEIGHT = 480

class Canvas {
    private m_elementHTML: HTMLElement = document.createElement('div')
    private m_width: number = CANVAS_WIDTH
    private m_height: number = CANVAS_HEIGHT
    private onCanvasClick = new Signal<void>()

    constructor() {
    }

    getOnCanvasClick() {
        return this.onCanvasClick
    }

    getDomElement() {
        return this.m_elementHTML
    }

    getWidth() {
        return this.m_width
    }

    getHeight() {
        return this.m_height
    }

    render(parentElement: HTMLElement) {
        this.m_elementHTML.innerHTML = ''

        this.m_elementHTML.classList.add('canvas')
        this.m_elementHTML.style.width = `${this.m_width}px`
        this.m_elementHTML.style.height = `${this.m_height}px`
        this.m_elementHTML.onmousedown = e => {
            if (!e.defaultPrevented) {
                this.onCanvasClick.dispatch()
            }
        }

        parentElement.appendChild(this.m_elementHTML)
    }
}

export {
    Canvas,
}