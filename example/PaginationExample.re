include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/PaginationExample.re')|}] |> Examples.prepCode;

let se = React.string;

let component = ReasonReact.statelessComponent("PaginationExample");

let make = _children => {
  ...component,
  render: _self =>
    <Examples.Example title="Pagination">
      <Pagination size=Pagination.Size.Small>
        <Pagination.Item>
          <Pagination.Link previous=true href="#" />
        </Pagination.Item>
        <Pagination.Item>
          <Pagination.Link href="#"> (se("1")) </Pagination.Link>
        </Pagination.Item>
        <Pagination.Item active=true>
          <Pagination.Link href="#"> (se("2")) </Pagination.Link>
        </Pagination.Item>
        <Pagination.Item>
          <Pagination.Link href="#"> (se("3")) </Pagination.Link>
        </Pagination.Item>
        <Pagination.Item>
          <Pagination.Link next=true href="#" />
        </Pagination.Item>
      </Pagination>
      <Pagination>
        <Pagination.Item>
          <Pagination.Link previous=true href="#" />
        </Pagination.Item>
        <Pagination.Item>
          <Pagination.Link href="#"> (se("1")) </Pagination.Link>
        </Pagination.Item>
        <Pagination.Item>
          <Pagination.Link href="#"> (se("2")) </Pagination.Link>
        </Pagination.Item>
        <Pagination.Item>
          <Pagination.Link href="#"> (se("3")) </Pagination.Link>
        </Pagination.Item>
        <Pagination.Item>
          <Pagination.Link next=true href="#" />
        </Pagination.Item>
      </Pagination>
      <Pagination size=Pagination.Size.Large>
        <Pagination.Item disabled=true>
          <Pagination.Link previous=true href="#" />
        </Pagination.Item>
        <Pagination.Item active=true>
          <Pagination.Link href="#"> (se("1")) </Pagination.Link>
        </Pagination.Item>
        <Pagination.Item>
          <Pagination.Link href="#"> (se("2")) </Pagination.Link>
        </Pagination.Item>
        <Pagination.Item>
          <Pagination.Link href="#"> (se("3")) </Pagination.Link>
        </Pagination.Item>
        <Pagination.Item>
          <Pagination.Link next=true href="#" />
        </Pagination.Item>
      </Pagination>
      (Examples.exampleHighlight(code))
    </Examples.Example>,
};
/**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
let make =
  ReasonReactCompat.wrapReasonReactForReact(
    ~component, (reactProps: {. "children": 'children}) =>
    make(reactProps##children)
  );
[@bs.obj]
external makeProps: (~children: 'children, unit) => {. "children": 'children} =
  "";
