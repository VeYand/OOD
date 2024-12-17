```mermaid
classDiagram

ShapeFactory ..> BaseShape
CanvasModel o-- BaseShape
CanvasModel ..|> ICanvasModel
Ellipse ..|> BaseShape
Rectangle ..|> BaseShape
Triangle ..|> BaseShape
ImageShape ..|> BaseShape
namespace Model {
    class ShapeFactory {
        + constructShape(type: ShapeType, data?: string): BaseShape
    }

    class ICanvasModel {
        <<interface>>
        + getShape(shapeId: string): BaseShape | undefined
        + getShapeIdToShapeMap(): Map<string, BaseShape>
        + getCanvasSize(): ShapeSize
    }

    class CanvasModel {
        - canvasSize: ShapeSize
        - shapes: Map<string, BaseShape>
        - shapeChangeObserver?: ShapeChangeObserver
        + addArtObject(type: ArtObjectType): void
        + addImage(data: string): void
        + updateShapeSizeAndPosition(shapeId: string, changes): void
        + setObserver(onShapeChange: ShapeChangeObserver): void
        + removeShape(shapeId: string): void
        + getShape(shapeId: string): BaseShape | undefined
        + getShapeIdToShapeMap(): Map<string, BaseShape>
        + getCanvasSize(): ShapeSize
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

App ..> CanvasModel
App o-- ICanvasModel
App o-- CanvasController
App ..> Canvas
App ..> Toolbar
Toolbar o-- CanvasController
Canvas o-- ICanvasModel
Canvas o-- CanvasController
Canvas ..> InteractiveShape
Canvas ..> EllipseShape
Canvas ..> RectangleShape
Canvas ..> TriangleShape
Canvas ..> ImageShape
namespace View {
    class App {
        - model: ICanvasModel
        - controller: CanvasController
        + handleSelectShape(shapeId?: string): void
        + handleDeleteShape(shapeId: string): void
        + render(): JSX.Element
    }

    class Canvas {
        - model: ICanvasModel
        - controller: CanvasController
        + renderShapes(): ReactElement[]
        + handleKeyDown(event: KeyboardEvent): void
        + render(): JSX.Element
    }

    class Toolbar {
        - controller: CanvasController
        + render(): JSX.Element
    }

    class InteractiveShape {
        - isDragging: boolean
        - isResizing: boolean
        + handleMouseDown(e: React.MouseEvent): void
        + handleMouseMove(e: MouseEvent): void
        + handleMouseUp(): void
        + render(): JSX.Element
    }

    class EllipseShape {
        + render(): JSX.Element
    }

    class TriangleShape {
        + render(): JSX.Element
    }

    class RectangleShape {
        + render(): JSX.Element
    }

    class ImageShape {
        + render(): JSX.Element
    }
}

CanvasController o-- CanvasModel
namespace Controller {
    class CanvasController {
        - model: CanvasModel
        + addArtObject(type: ArtObjectType): void
        + addImage(data: string): void
        + removeShape(shapeId: string): void
        + updateShapeSizeAndPosition(shapeId: string, changes): void
        + setObserver(onShapeChange: ShapeChangeObserver): void
    }
}
```
