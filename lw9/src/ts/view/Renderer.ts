class Renderer {
    private readonly m_element: HTMLElement

    constructor(tagName: string) {
        this.m_element = document.createElement(tagName)
    }

    removeFromDom() {
        this.m_element.remove()
    }

    getDomElement() {
        return this.m_element
    }

    getBoundingClientRect() {
        return this.m_element.getBoundingClientRect()
    }

    addEventListener(type: string, listener: EventListenerOrEventListenerObject) {
        this.m_element.addEventListener(type, listener)
    }

    removeEventListener(type: string, listener: EventListenerOrEventListenerObject) {
        this.m_element.removeEventListener(type, listener)
    }

    addClassName(className: string) {
        this.m_element.classList.add(className)
    }

    setInnerHTML(htmlValue: string) {
        this.m_element.innerHTML = htmlValue
    }

    setStyle(style: string, value: string) {
        this.m_element.style.setProperty(style, value)
    }

    appendChild(element: Element) {
        this.m_element.appendChild(element)
    }
}

export {
    Renderer,
}
