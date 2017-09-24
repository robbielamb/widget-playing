let component = ReasonReact.statelessComponent "Table";

let make
    tag::(tag: string)="table"
    bordered::(bordered: bool)=false
    striped::(striped: bool)=false
    inverse::(inverse: bool)=false
    hover::(hover: bool)=false
    reflow::(reflow: bool)=false
    small::(small: bool)=false
    responsive::(responsive: bool)=false
    responsiveTag::(responsiveTag: string)="div"
    classname::(classname: option string)=?
    children => {
  ...component,
  render: fun _self => {
    let classes =
      [
        "table",
        bordered ? "table-bordered" : "",
        striped ? "table-striped" : "",
        inverse ? "table-inverse" : "",
        hover ? "table-hover" : "",
        reflow ? "table-reflow" : "",
        small ? "table-small" : "",
        Utils.unwrapStr Utils.i classname
      ]
      |> String.concat " ";
    let table = ReasonReact.createDomElement tag props::{"className": classes} children;

    switch responsive {
    | true => ReasonReact.createDomElement responsiveTag props::{"className": "table-responsive"} [|table|]
    | false => table
    }
  }
};