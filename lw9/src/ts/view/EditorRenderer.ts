import {ToolbarRenderer} from "./ToolbarRenderer";
import {CanvasRenderer} from "./CanvasRenderer";
import {Renderer} from "./Renderer";
import {TagName} from "../common/TagName";
import {EditorModel} from "../model/EditorModel";
import {EditorController} from "../controller/EditorController";
import {SelectionModel} from "../model/SelectionModel";


class EditorRenderer {
    private m_model: EditorModel
    private m_controller: EditorController
    private m_renderer = new Renderer(TagName.DIV)
    private m_workspaceRenderer = new Renderer(TagName.DIV)
    private m_toolbarRenderer: ToolbarRenderer
    private m_canvasRenderer: CanvasRenderer

    constructor(model: EditorModel) {
        this.m_renderer.addClassName('main-container')
        this.m_workspaceRenderer.addClassName('workspace')

        this.m_model = model
        const selectionModel = new SelectionModel()

        this.m_controller = new EditorController(model, selectionModel)

        this.m_canvasRenderer = new CanvasRenderer(model.canvasModel, selectionModel)

        this.m_toolbarRenderer = new ToolbarRenderer()
        this.m_toolbarRenderer.getOnSaveSignal().add(() => this.m_controller.saveEditor())
        this.m_toolbarRenderer.getOnUploadSignal().add(() => this.m_controller.uploadFile())
        this.m_toolbarRenderer.getOnCreateShapeSignal().add(shapeType => this.m_controller.addShape(shapeType))
        this.m_toolbarRenderer.getOnDeleteShapeSignal().add(() => this.m_controller.deleteSelectedShape())

        this.m_model.getOnUploadState().add(() => this.updateCanvasRenderer())
    }

    updateCanvasRenderer() {
        this.m_canvasRenderer.clear()
        const selectionModel = new SelectionModel()
        this.m_canvasRenderer = new CanvasRenderer(this.m_model.canvasModel, selectionModel)
        this.m_canvasRenderer.render(this.m_workspaceRenderer.getDomElement())
    }

    render(parentElement: HTMLElement) {
        this.m_renderer.removeFromDom()

        const editorHTML = this.m_renderer.getDomElement()
        const workspaceHTML = this.m_workspaceRenderer.getDomElement()

        parentElement.appendChild(editorHTML)

        this.m_toolbarRenderer.render(editorHTML)
        this.m_renderer.appendChild(workspaceHTML)

        this.m_canvasRenderer.render(workspaceHTML)
    }
}

export {
    EditorRenderer,
}