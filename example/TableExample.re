include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/TableExample.re')|}] |> Examples.prepCode;

let se = ReasonReact.string;

let component = ReasonReact.statelessComponent("TableExample");
let make = _children => {
  ...component,
  render: _self =>
    <Examples.Example title="Table example">
      <Table bordered=true striped=true hover=true>
        <thead>
          <tr>
            <th> (se("Col 1")) </th>
            <th> (se("Col 2")) </th>
            <th> (se("Col 3")) </th>
            <th> (se("Col 4")) </th>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td> (se("Row 1, col 1")) </td>
            <td> (se("Row 1, col 2")) </td>
            <td> (se("Row 1, col 3")) </td>
            <td> (se("Row 1, col 4")) </td>
          </tr>
          <tr>
            <td> (se("Row 2, col 1")) </td>
            <td> (se("Row 2, col 2")) </td>
            <td> (se("Row 2, col 3")) </td>
            <td> (se("Row 2, col 4")) </td>
          </tr>
          <tr>
            <td> (se("Row 3, col 1")) </td>
            <td> (se("Row 3, col 2")) </td>
            <td> (se("Row 3, col 3")) </td>
            <td> (se("Row 3, col 4")) </td>
          </tr>
          <tr>
            <td> (se("Row 4, col 1")) </td>
            <td> (se("Row 4, col 2")) </td>
            <td> (se("Row 4, col 3")) </td>
            <td> (se("Row 4, col 4")) </td>
          </tr>
        </tbody>
      </Table>
      (Examples.highlight(code))
    </Examples.Example>,
};
