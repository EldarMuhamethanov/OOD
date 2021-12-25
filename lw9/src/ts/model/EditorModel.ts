import {CanvasModel} from "./CanvasModel";
import {ShapeType} from "../common/ShapeType";
import {download} from "../common/download";
import {ShapeFactory} from "../factory/ShapeFactory";
import {uploadFile} from "../common/uploadFile";
import {Signal} from "../common/Signal";

const CANVAS_WIDTH = 640
const CANVAS_HEIGHT = 480

type EditorStateShape = {
    id: string,
    left: number,
    top: number,
    type: ShapeType,
    width: number,
    height: number,
}

type EditorState = {
    canvasWidth: number,
    canvasHeight: number,
    shapes: Array<EditorStateShape>,
}

class EditorModel {
    private m_canvasModel: CanvasModel
    private m_onUploadState = new Signal<void>()

    constructor() {
        this.m_canvasModel = new CanvasModel(CANVAS_WIDTH, CANVAS_HEIGHT)
    }

    get canvasModel() {
        return this.m_canvasModel
    }

    getOnUploadState() {
        return this.m_onUploadState
    }

    uploadFile() {
        uploadFile(
            newState => {
                const remappedState = newState as EditorState
                this.m_canvasModel = new CanvasModel(remappedState.canvasWidth, remappedState.canvasHeight)
                remappedState.shapes
                    .forEach(stateShape => {
                        const shapeModel = ShapeFactory.createShapeModel({
                            shapeType: stateShape.type,
                            canvas: this.m_canvasModel,
                            top: stateShape.top,
                            left: stateShape.left,
                            width: stateShape.width,
                            height: stateShape.height
                        })
                        this.m_canvasModel.addShape(shapeModel)
                    })
                this.m_onUploadState.dispatch()
            }
        )
    }

    saveEditor() {
        download(JSON.stringify(this.m_canvasModel.toJson()), 'editor.json')
    }
}

export {
    EditorModel,
}