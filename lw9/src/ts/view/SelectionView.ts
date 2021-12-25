import {ResizeHandler} from "../handlers/ResizeHandler";
import {Renderer} from "./Renderer";
import {TagName} from "../common/TagName";
import {Shape} from "../model/Shape";
import {SelectionModel} from "../model/SelectionModel";
import {SelectionController} from "../controller/SelectionController";

class SelectionView {
    private m_model: SelectionModel
    private m_controller: SelectionController
    private m_renderer: Renderer = new Renderer(TagName.DIV)
    private m_resizeHandler: ResizeHandler
    private m_parentElement: HTMLElement
    private m_onShapeRectChangeUnsub: (() => void) | null = null

    constructor(model: SelectionModel, parentElement: HTMLElement) {
        this.m_model = model
        this.m_controller = new SelectionController(model, this)
        this.m_renderer.addClassName('selection')
        this.m_parentElement = parentElement

        this.m_resizeHandler = new ResizeHandler(this.m_renderer.getDomElement())

        this.m_model.onSelectedShapeChanged().add(() => this.handleChangeSelectedShape())
    }

    private setBoundsByShape(shape: Shape) {
        this.m_renderer.setStyle('width', `${shape.width}px`)
        this.m_renderer.setStyle('height', `${shape.height}px`)
        this.m_renderer.setStyle('left', `${shape.left}px`)
        this.m_renderer.setStyle('top', `${shape.top}px`)
    }

    private handleResetSelection() {
        this.m_renderer.removeFromDom()
        if (this.m_onShapeRectChangeUnsub) {
            this.m_onShapeRectChangeUnsub()
            this.m_onShapeRectChangeUnsub = null
        }
        this.m_resizeHandler.getOnRectChangeSignal().clearListeners()
    }

    private handleChangeSelectedShape() {
        this.handleResetSelection()
        const selectedShape = this.m_model.getSelectedShape()
        if (!selectedShape) {
            return
        }
        this.m_onShapeRectChangeUnsub = selectedShape.getOnRectChange().add(() => this.setBoundsByShape(selectedShape))
        this.m_resizeHandler.getOnRectChangeSignal().add(rect => {
            const parentBounds = this.m_parentElement.getBoundingClientRect()
            this.m_controller.resize({
                ...rect,
                left: rect.left - parentBounds.left,
                top: rect.top - parentBounds.top,
            })
        })
        this.setBoundsByShape(selectedShape)
        this.m_parentElement.appendChild(this.m_renderer.getDomElement())
    }
}

export {
    SelectionView,
}