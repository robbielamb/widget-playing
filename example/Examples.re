include Bootstrap;

//[@bs.module] external logo: string = "./logo.svg";

let se = React.string;

let exampleHighlight = code => <Highlight languages={Some([|"html"|])}> {se(code)} </Highlight>;

let highlight = exampleHighlight;

let prepCode = (code: string): string => {
  //Js.log(code);
  code |> Js.String.split("\n") |> Js.Array.sliceFrom(7) |> Js.Array.joinWith("\n");
  
}

module Example = {
  /*  let component = ReasonReact.statelessComponent("Example"); */
  [@react.component]
  let make = (~title, ~children) => {
    <Layout.Row className="mb-4 border p-2">
      <Layout.Col> 
        <h3> {se(title)} </h3> 
        {children}
       </Layout.Col>
    </Layout.Row>;
  };
};