import {Signal} from "../common/Signal";
import {ShapeType} from "../common/ShapeType";
import {ButtonRenderer} from "./ButtonRenderer";
import {Renderer} from "./Renderer";
import { TagName } from "../common/TagName";


class ToolbarRenderer {
    private m_renderer: Renderer = new Renderer(TagName.DIV)
    private onSaveSignal = new Signal<void>()
    private onUploadSignal = new Signal<void>()
    private onCreateShapeSignal = new Signal<ShapeType>()
    private onDeleteShapeSignal = new Signal<void>()

    private m_saveButton: ButtonRenderer
    private m_uploadButton: ButtonRenderer
    private m_createRectangleButton: ButtonRenderer
    private m_createTriangleButton: ButtonRenderer
    private m_createEllipseButton: ButtonRenderer
    private m_onDeleteShapeButton: ButtonRenderer

     constructor() {
        this.m_renderer.addClassName('toolbar')
        this.m_saveButton = new ButtonRenderer(
            'Save',
            () => this.onSaveSignal.dispatch(),
            ['button']
        )
        this.m_uploadButton = new ButtonRenderer(
            'Upload',
            () => this.onUploadSignal.dispatch(),
            ['button']
        )
        this.m_createRectangleButton = new ButtonRenderer(
            'Rect',
            () => this.onCreateShapeSignal.dispatch('rectangle'),
            ['button']
        )
        this.m_createTriangleButton = new ButtonRenderer(
            'Triangle',
            () => this.onCreateShapeSignal.dispatch('triangle'),
            ['button']
        )
        this.m_createEllipseButton = new ButtonRenderer(
            'Ellipse',
            () => this.onCreateShapeSignal.dispatch('ellipse'),
            ['button']
        )
        this.m_onDeleteShapeButton = new ButtonRenderer(
            'Delete',
            () => this.onDeleteShapeSignal.dispatch(),
            ['button']
        )
    }

    getOnUploadSignal() {
        return this.onUploadSignal
    }

    getOnSaveSignal() {
        return this.onSaveSignal
    }

    getOnCreateShapeSignal() {
        return this.onCreateShapeSignal
    }

    getOnDeleteShapeSignal() {
        return this.onDeleteShapeSignal
    }

    render(parentElement: HTMLElement) {
        const toolbarHTML = this.m_renderer.getDomElement()
        this.m_saveButton.render(toolbarHTML)
        this.m_uploadButton.render(toolbarHTML)
        this.m_createRectangleButton.render(toolbarHTML)
        this.m_createEllipseButton.render(toolbarHTML)
        this.m_createTriangleButton.render(toolbarHTML)
        this.m_onDeleteShapeButton.render(toolbarHTML)

        parentElement.appendChild(toolbarHTML)
    }
}

export {
    ToolbarRenderer,
}