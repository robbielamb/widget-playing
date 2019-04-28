include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/PaginationExample.re').default|}] |> Examples.prepCode;

let se = React.string;



[@react.component]
let make = () => {
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
