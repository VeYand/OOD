Архитектура актуальна до коммита 2bbf6118 
```mermaid
classDiagram

ShapeFactory ..> BaseShape
CanvasModel o-- BaseShape
CanvasModel ..|> ICanvasModel
BaseShape ..|> IShape
Ellipse ..|> BaseShape
Rectangle ..|> BaseShape
Triangle ..|> BaseShape
ImageShape ..|> BaseShape
ICanvasModel ..> IShape

AbstractCommand ..|> ICommand
InsertArtObjectCommand o-- CanvasModel
InsertArtObjectCommand ..|> AbstractCommand
InsertImageObjectCommand o-- CanvasModel
InsertImageObjectCommand ..|> AbstractCommand
UpdateShapeSizeAndPositionCommand o-- CanvasModel
UpdateShapeSizeAndPositionCommand ..|> AbstractCommand
RemoveShapeCommand o-- CanvasModel
RemoveShapeCommand ..|> AbstractCommand
RemoveShapeCommand o-- BaseShape
RemoveShapeCommand o-- CanvasModel
LoadJsonCommand ..|> AbstractCommand
History o-- ICommand

namespace Command {
    class History {
        + canUndo(): boolean
        + canRedo(): boolean
        + undo()
        + redo()
        + addAndExecuteCommand(command: ICommand)
    }

    class ICommand {
        <<interface>>
        + execute()
	    + unexecute()
	    + destroy()
	    + canMergeWith(command: ICommand): boolean
	    + mergeWith(command: ICommand)
    }

    class AbstractCommand {
        - executed: boolean
        + execute()
	    + unexecute()
	    + canMergeWith(command: ICommand): boolean
	    + mergeWith(command: ICommand)
	    + destroy()*
        # doExecute()*
	    # doUnexecute()*
    }

    class InsertArtObjectCommand {
        - insertedShapeId: ?string
        + doExecute()
	    + doUnexecute()
        + destroy()
    }

    class InsertImageObjectCommand {
        - insertedShapeId: ?string
        - shouldDelete: boolean
        - data: ?string
        + doExecute()
	    + doUnexecute()
        + destroy()
    }

    class UpdateShapeSizeAndPositionCommand {
        - oldSize: ?ShapeSize
        - oldPosition: ?ShapePosition
        + doExecute()
	    + doUnexecute()
        + destroy()
    }

    class RemoveShapeCommand {
        - shape: ?BaseShape
        + doExecute()
	    + doUnexecute()
        + destroy()
    }

    class LoadJsonCommand {
        - oldJsonState: ?string
        + doExecute()
	    + doUnexecute()
        + destroy()
    }
}

namespace Model {
    class ShapeFactory {
        + constructShape(type: ShapeType, data?: string): BaseShape
    }

    class ICanvasModel {
        <<interface>>
        + getShape(shapeId: string): IShape
        + getShapeIdToShapeMap(): Map<string, IShape>
        + getCanvasSize(): ShapeSize
        + serializeCanvasToJson(): string
    }

    class CanvasModel {
        - canvasSize: ShapeSize
        - shapes: Map<string, BaseShape>
        - shapeChangeObservers: ShapeChangeObserver[]
        + loadCanvasFromJson(jsonData: string): void
        + serializeCanvasToJson(): string
        + addArtObject(type: ArtObjectType): void
        + addImage(data: string): void
        + updateShapeSizeAndPosition(shapeId: string, changes): void
        + addObserver(onShapeChange: ShapeChangeObserver): void
        + removeObserver(onShapeChange: ShapeChangeObserver): void
        + removeShape(shapeId: string): void
        + getShape(shapeId: string): BaseShape | undefined
        + getShapeIdToShapeMap(): Map<string, BaseShape>
        + getCanvasSize(): ShapeSize
    }

    class IShape {
        <<interface>>
        + getPosition(): ShapePosition
        + getSize(): ShapeSize
        + move(position: ShapePosition): void
    }

    class BaseShape {
        - position: ShapePosition
        - size: ShapeSize
        + getPosition(): ShapePosition
        + getSize(): ShapeSize
        + resize(size: ShapeSize): void
        + move(position: ShapePosition): void
        + getType()*: ShapeType
    }

    class Ellipse {
        + getType(): ShapeType
    }

    class Rectangle {
        + getType(): ShapeType
    }

    class Triangle {
        + getType(): ShapeType
    }

    class ImageShape {
        - data: string
        + getType(): ShapeType
        + getData(): string
    }
}

App o-- ICanvasModel
App o-- CanvasController
App o-- ShapeController
App ..> Canvas
App ..> Toolbar
Toolbar o-- CanvasController
Canvas o-- ICanvasModel
Canvas o-- ShapeController
Canvas o-- CanvasController
Canvas ..> InteractiveShape
Canvas ..> EllipseShape
Canvas ..> RectangleShape
Canvas ..> TriangleShape
Canvas ..> ImageShapeComponent
InteractiveShape o-- ShapeController
namespace View {
    class App {
        - model: ICanvasModel
        - canvasController: CanvasController
        - shapeController: ShapeContoller
        + handleSelectShape(shapeId?: string): void
        + handleDeleteShape(shapeId: string): void
        + render(): ReactElement
    }

    class Canvas {
        - model: ICanvasModel
        - canvasController: CanvasController
        - shapeController: ShapeController
        + renderShapes(): ReactElement[]
        + handleKeyDown(event: KeyboardEvent): void
        + render(): ReactElement
    }

    class Toolbar {
        - canvasController: CanvasController
        + render(): ReactElement
    }

    class InteractiveShape {
        - isDragging: boolean
        - isResizing: boolean
        - shapeController: ShapeContoller
        + handleMouseDown(e: React.MouseEvent): void
        + handleMouseMove(e: MouseEvent): void
        + handleMouseUp(): void
        + render(): ReactElement
    }

    class EllipseShape {
        + render(): ReactElement
    }

    class TriangleShape {
        + render(): ReactElement
    }

    class RectangleShape {
        + render(): ReactElement
    }

    class ImageShapeComponent {
        + render(): ReactElement
    }
}

CanvasController o-- CanvasModel
CanvasController o-- History
ShapeController o-- CanvasModel
CanvasController o-- History
namespace Controller {
    class CanvasController {
        - model: CanvasModel
        - history: History
        + undo()
        + redo()
        + canUndo(): boolean
        + canRedo(): boolean
        + loadCanvasFromJson(jsonString: string)
        + addArtObject(type: ArtObjectType): void
        + addImage(data: string): void
        + removeShape(shapeId: string): void
        + addObserver(onShapeChange: ShapeChangeObserver): void
        + removeObserver(onShapeChange: ShapeChangeObserver): void
    }

    class ShapeController {
        - model: CanvasModel
        - history: History
        + updateShapeSizeAndPosition(shapeId: string, changes): void
        + handleMove(shapeId, initialPosition, deltaX, deltaY): void
        + handleResize(shapeId: string, initial, delta: ShapePosition, resizeCorner: string): void
    }
}
```
