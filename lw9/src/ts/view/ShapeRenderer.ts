import {Shape} from "../model/Shape";
import {ShapeController} from "../controller/ShapeController";
import {DragNDropHandler} from "../handlers/DragNDropHandler";
import {Signal} from "../common/Signal";
import {CanvasRenderer} from "./CanvasRenderer";
import {Renderer} from "./Renderer";
import { TagName } from "../common/TagName";
import {CanvasModel} from "../model/CanvasModel";


abstract class ShapeRenderer
{
    private readonly m_model: Shape
    private readonly m_controller: ShapeController
    private m_svgElement: SVGGraphicsElement = document.createElementNS('http://www.w3.org/2000/svg', 'svg')
    private onSelectSignal = new Signal<void>()

    protected constructor(model: Shape, canvasModel: CanvasModel) {
        this.m_svgElement.classList.add('shape')
        this.m_svgElement.style.setProperty('pointer-events', 'none')
        this.m_svgElement.style.setProperty('pointer-events', 'none')

        this.m_model = model
        this.m_controller = new ShapeController(model, canvasModel)

        this.m_model.getOnRectChange().add(() => this.rerender())
    }

    getOnSelectSignal() {
        return this.onSelectSignal
    }

    get model() {
        return this.m_model
    }

    get controller() {
        return this.m_controller
    }

    removeFromDom() {
        this.m_svgElement.remove()
    }

    protected abstract updateSvgBounds(): void
    protected abstract getShapeHtmlImpl(): SVGGraphicsElement

    private rerender() {
        const left = this.m_model.left
        const top = this.m_model.top
        const width = this.m_model.width
        const height = this.m_model.height

        this.m_svgElement.style.setProperty('left', `${left}px`)
        this.m_svgElement.style.setProperty('top', `${top}px`)
        this.m_svgElement.style.setProperty('width', `${width}px`)
        this.m_svgElement.style.setProperty('height', `${height}px`)

        this.m_svgElement.setAttribute('viewPort', `0 0 ${width} ${height}`)
        this.updateSvgBounds()
    }

    render(parentElement: HTMLElement) {
        this.removeFromDom()
        this.m_svgElement.setAttribute('xmlns', 'http://www.w3.org/2000/svg')
        this.rerender()
        const svgImpl = this.getShapeHtmlImpl()
        svgImpl.style.setProperty('pointer-events', 'all')
        this.m_svgElement.appendChild(svgImpl)

        const dndHandler = new DragNDropHandler(svgImpl)
        dndHandler.getOnMoveSignal().add(newPosition => {
            const parentBounds = parentElement.getBoundingClientRect()
            this.m_controller.shapeMove({
                left: newPosition.left - parentBounds.left,
                top: newPosition.top - parentBounds.top,
            })
        })

        svgImpl.addEventListener('mousedown', e => {
            e.preventDefault()
            this.onSelectSignal.dispatch()
        })

        parentElement.appendChild(this.m_svgElement)
    }
}

export {
    ShapeRenderer,
}