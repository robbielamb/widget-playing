include Bootstrap;


[@bs.module] external logo : string = "./logo.svg";

let se = ReasonReact.stringToElement;

let exampleHighlight = code =>
  <Highlight languages=[|"html"|]> (se(code)) </Highlight>;

let highlight = exampleHighlight;

let prepCode = (code: string) : string =>
  code
  |> Js.String.split("\n")
  |> Js.Array.sliceFrom(7)
  |> Js.Array.joinWith("\n");

module Example = {
  let component = ReasonReact.statelessComponent("Example");
  let make = (~title, children: array(ReasonReact.reactElement)) => {
    ...component,
    render: _self => {
      let title = <h3> (se(title)) </h3>;
      let _ = Js.Array.unshift(title, children);
      let col = ReasonReact.element(Layout.Col.make(children));
      <Layout.Row className="mb-4 border p-2"> col </Layout.Row>;
    }
  };
};