include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/PaginationExample.re')|}] |> Examples.prepCode;

let se = ReasonReact.string;

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
    </Examples.Example>
};