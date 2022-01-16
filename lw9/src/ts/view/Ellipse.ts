import {ShapeRenderer} from "./ShapeRenderer";
import {Shape} from "../model/Shape";
import {CanvasRenderer} from "./CanvasRenderer";
import {CanvasModel} from "../model/CanvasModel";


class EllipseRenderer extends ShapeRenderer
{
    private m_implElement: SVGGraphicsElement = document.createElementNS('http://www.w3.org/2000/svg', 'ellipse')

    constructor(model: Shape, canvas: CanvasModel) {
        super(model, canvas)
    }

    protected updateSvgBounds() {
        const model = this.model
        const width = model.width
        const height = model.height
        this.m_implElement.setAttribute('rx', `${width / 2}`)
        this.m_implElement.setAttribute('ry', `${height / 2}`)
        this.m_implElement.setAttribute('cx', `${width / 2}`)
        this.m_implElement.setAttribute('cy', `${height / 2}`)
        this.m_implElement.setAttribute('fill', 'green')
    }

    protected getShapeHtmlImpl(): SVGGraphicsElement {
        return this.m_implElement
    }
}

export {
    EllipseRenderer,
}